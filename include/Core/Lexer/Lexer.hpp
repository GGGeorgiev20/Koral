#pragma once

#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>

#include "Common/Token.hpp"

class Lexer
{
public:
    Lexer(std::string content) : m_content(std::move(content)), m_char(m_content[0]) {};

    std::vector<Token> Scan();

private:
    void Consume();

    void Next();

    char Peek();

    void AddToken(std::uint8_t type, const std::string& value, size_t line);

    // --- Skipping content ---

    void SkipWhitespace();

    void SkipComment(bool multiline);

    // --- Reading specific token types ---

    void ReadIdentifier();

    void ReadString();

    char EscapeCharacter();

    void ReadNumber();

private:
    std::string m_content;

    char m_char;
    size_t m_pos = 0;
    size_t m_line = 1;

    std::vector<Token> m_tokens = {};

    // --- Token identification variables ---

    const std::unordered_map<char, uint8_t> character_type_map = {
        { ';', TOKEN_SEMICOLON },
        { '(', TOKEN_LPAREN },
        { ')', TOKEN_RPAREN },
        { ',', TOKEN_COMMA },
        { '+', TOKEN_PLUS },
        { '-', TOKEN_MINUS }
    };

    const std::unordered_map<char, uint8_t> character_equal_comb = {
        { '=', TOKEN_EQ },
        { '+', TOKEN_PLUS_EQ },
        { '-', TOKEN_MINUS_EQ },
        { '!', TOKEN_NOT_EQ },
        { '<', TOKEN_LTE },
        { '>', TOKEN_GTE }
    };
};
