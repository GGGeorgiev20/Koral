#include <gtest/gtest.h>
#include "test_utils.hpp"
#include "Common/Token.hpp"
#include "Core/Lexer/Lexer.hpp"

// NOTE: Tests are written by ChatGPT

// 1️⃣ String literal
TEST(LexerTest, LexesStringCorrect) {
    std::string to_lex = "\"test\"";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_STRING, .value = "test", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 2️⃣ Identifier
TEST(LexerTest, LexesIdentifier) {
    std::string to_lex = "variable";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "variable", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 3️⃣ Integer literal
TEST(LexerTest, LexesIntegerLiteral) {
    std::string to_lex = "42";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_NUMBER, .value = "42", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 4️⃣ Simple arithmetic
TEST(LexerTest, LexesArithmeticExpression) {
    std::string to_lex = "a + b * 5";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "a", .line = 1 },
        { .type = TOKEN_PLUS, .value = "+", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "b", .line = 1 },
        { .type = TOKEN_ASTERISK, .value = "*", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "5", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 5️⃣ Assignment and comparison
TEST(LexerTest, LexesAssignmentAndComparison) {
    std::string to_lex = "x = 10; y += 5; if (x >= y) x = y;";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "x", .line = 1 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "10", .line = 1 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "y", .line = 1 },
        { .type = TOKEN_PLUS_EQ, .value = "+=", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "5", .line = 1 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "if", .line = 1 },
        { .type = TOKEN_LPAREN, .value = "(", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "x", .line = 1 },
        { .type = TOKEN_GTE, .value = ">=", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "y", .line = 1 },
        { .type = TOKEN_RPAREN, .value = ")", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "x", .line = 1 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "y", .line = 1 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 6️⃣ Parentheses and punctuation
TEST(LexerTest, LexesFunctionCall) {
    std::string to_lex = "print(a, b)";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "print", .line = 1 },
        { .type = TOKEN_LPAREN, .value = "(", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "a", .line = 1 },
        { .type = TOKEN_COMMA, .value = ",", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "b", .line = 1 },
        { .type = TOKEN_RPAREN, .value = ")", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 7️⃣ Handles comments
TEST(LexerTest, IgnoresSingleLineComment) {
    std::string to_lex = "x = 1; // comment\n y = 2;";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "x", .line = 1 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "1", .line = 1 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "y", .line = 2 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 2 },
        { .type = TOKEN_NUMBER, .value = "2", .line = 2 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 2 },
        { .type = TOKEN_EOF, .value = "", .line = 2 },
    };

    EXPECT_EQ(result, expected);
}

// 8️⃣ Handles string with escaped quotes
TEST(LexerTest, HandlesEscapedQuotes) {
    std::string to_lex = "\"He said, \\\"hi\\\"\"";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_STRING, .value = "He said, \"hi\"", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}

// 9️⃣ Multi-line input tracking
TEST(LexerTest, TracksMultipleLines) {
    std::string to_lex = "a = 1;\n\nb = 2;";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "a", .line = 1 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "1", .line = 1 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "b", .line = 3 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 3 },
        { .type = TOKEN_NUMBER, .value = "2", .line = 3 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 3 },
        { .type = TOKEN_EOF, .value = "", .line = 3 },
    };

    EXPECT_EQ(result, expected);
}

// 🔟 Complex expression with operators
TEST(LexerTest, LexesComplexExpression) {
    std::string to_lex = "count = (a + b) * 2 - 5 / c;";
    Lexer lexer(to_lex);

    std::vector<Token> result = lexer.Scan();
    std::vector<Token> expected = {
        { .type = TOKEN_IDENTIFIER, .value = "count", .line = 1 },
        { .type = TOKEN_ASSIGN, .value = "=", .line = 1 },
        { .type = TOKEN_LPAREN, .value = "(", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "a", .line = 1 },
        { .type = TOKEN_PLUS, .value = "+", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "b", .line = 1 },
        { .type = TOKEN_RPAREN, .value = ")", .line = 1 },
        { .type = TOKEN_ASTERISK, .value = "*", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "2", .line = 1 },
        { .type = TOKEN_MINUS, .value = "-", .line = 1 },
        { .type = TOKEN_NUMBER, .value = "5", .line = 1 },
        { .type = TOKEN_SLASH, .value = "/", .line = 1 },
        { .type = TOKEN_IDENTIFIER, .value = "c", .line = 1 },
        { .type = TOKEN_SEMICOLON, .value = ";", .line = 1 },
        { .type = TOKEN_EOF, .value = "", .line = 1 },
    };

    EXPECT_EQ(result, expected);
}
