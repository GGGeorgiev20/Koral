#pragma once

#include <cstdint>
#include <string>

struct Token
{
    uint8_t type;
    std::string value;
    size_t line;
};

enum : uint8_t
{
    // Special
    TOKEN_EOF,
    TOKEN_ILLEGAL,

    // ——— Literals ———
    TOKEN_IDENTIFIER, // variable/function names
    TOKEN_NUMBER,     // numeric literals
    TOKEN_STRING,     // string literals
    TOKEN_CHAR,       // character literals

    // ——— Operators ———
    // Arithmetic
    TOKEN_PLUS,       // +
    TOKEN_MINUS,      // -
    TOKEN_ASTERISK,   // *
    TOKEN_SLASH,      // /
    TOKEN_PERCENT,    // %

    // Assignment & comparison
    TOKEN_ASSIGN,     // =
    TOKEN_PLUS_EQ,    // +=
    TOKEN_MINUS_EQ,   // -=
    TOKEN_MULT_EQ,    // *=
    TOKEN_DIVIS_EQ,   // /=
    TOKEN_PERCE_EQ,   // %=
    TOKEN_EQ,         // ==
    TOKEN_NOT_EQ,     // !=
    TOKEN_LT,         // <
    TOKEN_GT,         // >
    TOKEN_LTE,        // <=
    TOKEN_GTE,        // >=

    // Bitwise & logical (if your language has them)
    TOKEN_AND,        // &
    TOKEN_OR,         // |
    TOKEN_XOR,        // ^
    TOKEN_NOT,        // !
    TOKEN_AND_AND,    // &&
    TOKEN_OR_OR,      // ||

    // ——— Delimiters & Punctuation ———
    TOKEN_COMMA,         // ,
    TOKEN_SEMICOLON,     // ;
    TOKEN_COLON,         // :
    TOKEN_DOT,           // .
    // TOKEN_ELLIPSIS,      // ...
    TOKEN_ARROW,         // ->

    // Parentheses, braces, brackets
    TOKEN_LPAREN,        // (
    TOKEN_RPAREN,        // )
    TOKEN_LBRACE,        // {
    TOKEN_RBRACE,        // }
    TOKEN_LBRACKET,      // [
    TOKEN_RBRACKET,      // ]

    // ——— Keywords ———
    // TOKEN_KW_IF,
    // TOKEN_KW_ELSE,
    // TOKEN_KW_FOR,
    // TOKEN_KW_WHILE,
    // TOKEN_KW_RETURN,
    // TOKEN_KW_FUNC,
    // TOKEN_KW_VAR,
    // TOKEN_KW_CONST,
};
