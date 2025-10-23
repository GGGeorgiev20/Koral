#pragma once

#include "Common/Token.hpp"

#include <string>
#include <cstdint>
#include <ostream>

inline std::string TokenTypeToString(uint8_t type)
{
    switch (type)
    {
        case TOKEN_EOF:
            return "TOKEN_EOF";
        case TOKEN_ILLEGAL:
            return "TOKEN_ILLEGAL";
        case TOKEN_UNTERMINATED:
            return "TOKEN_UNTERMINATED";
        case TOKEN_IDENTIFIER:
            return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER:
            return "TOKEN_NUMBER";
        case TOKEN_STRING:
            return "TOKEN_STRING";
        case TOKEN_CHAR:
            return "TOKEN_CHAR";
        case TOKEN_PLUS:
            return "TOKEN_PLUS";
        case TOKEN_MINUS:
            return "TOKEN_MINUS";
        case TOKEN_ASTERISK:
            return "TOKEN_ASTERISK";
        case TOKEN_SLASH:
            return "TOKEN_SLASH";
        case TOKEN_PERCENT:
            return "TOKEN_PERCENT";
        case TOKEN_ASSIGN:
            return "TOKEN_ASSIGN";
        case TOKEN_PLUS_EQ:
            return "TOKEN_PLUS_EQ";
        case TOKEN_MINUS_EQ:
            return "TOKEN_MINUS_EQ";
        case TOKEN_MULT_EQ:
            return "TOKEN_MULT_EQ";
        case TOKEN_DIVIS_EQ:
            return "TOKEN_DIVIS_EQ";
        case TOKEN_PERCE_EQ:
            return "TOKEN_PERCE_EQ";
        case TOKEN_EQ:
            return "TOKEN_EQ";
        case TOKEN_NOT_EQ:
            return "TOKEN_NOT_EQ";
        case TOKEN_LT:
            return "TOKEN_LT";
        case TOKEN_GT:
            return "TOKEN_GT";
        case TOKEN_LTE:
            return "TOKEN_LTE";
        case TOKEN_GTE:
            return "TOKEN_GTE";
        case TOKEN_AND:
            return "TOKEN_AND";
        case TOKEN_OR:
            return "TOKEN_OR";
        case TOKEN_XOR:
            return "TOKEN_XOR";
        case TOKEN_NOT:
            return "TOKEN_NOT";
        case TOKEN_AND_AND:
            return "TOKEN_AND_AND";
        case TOKEN_OR_OR:
            return "TOKEN_OR_OR";
        case TOKEN_COMMA:
            return "TOKEN_COMMA";
        case TOKEN_SEMICOLON:
            return "TOKEN_SEMICOLON";
        case TOKEN_COLON:
            return "TOKEN_COLON";
        case TOKEN_DOT:
            return "TOKEN_DOT";
        case TOKEN_ARROW:
            return "TOKEN_ARROW";
        case TOKEN_LPAREN:
            return "TOKEN_LPAREN";
        case TOKEN_RPAREN:
            return "TOKEN_RPAREN";
        case TOKEN_LBRACE:
            return "TOKEN_LBRACE";
        case TOKEN_RBRACE:
            return "TOKEN_RBRACE";
        case TOKEN_LBRACKET:
            return "TOKEN_LBRACKET";
        case TOKEN_RBRACKET:
            return "TOKEN_RBRACKET";
        default:
            return "TOKEN_UNKNOWN";
    }
}

inline void PrintTo(const Token& t, std::ostream* os)
{
    *os << "Token(type=" << TokenTypeToString(t.type)
        << ", value=\"" << t.value << "\""
        << ", line=" << t.line << ")";
}
