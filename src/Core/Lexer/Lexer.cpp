#include "Core/Lexer/Lexer.hpp"

#include "Common/Token.hpp"

#include <cctype>

std::vector<Token> Lexer::Scan()
{
    this->SkipWhitespace();

    while (m_char != '\0')
    {
        this->Consume();
    }

    this->AddToken(TOKEN_EOF, "", m_line);

    return m_tokens;
}

void Lexer::Consume()
{
    if (std::isalpha(m_char) || m_char == '_')
    {
        return this->ReadIdentifier();
    }

    if (std::isdigit(m_char))
    {
        return this->ReadNumber();
    }

    switch (m_char)
    {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return this->SkipWhitespace();
        case '*':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_MULT_EQ, "*=", m_line);
            }
            else this->AddToken(TOKEN_ASTERISK, "*", m_line);
            break;
        case '/':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_DIVIS_EQ, "/=", m_line);
            }
            else if (this->Peek() == '/') return this->SkipComment(false);
            else if (this->Peek() == '*') return this->SkipComment(true);
            else this->AddToken(TOKEN_SLASH, "/", m_line);
            break;
        case '+':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_PLUS_EQ, "+=", m_line);
            }
            else this->AddToken(TOKEN_PLUS, "+", m_line);
            break;
        case '-':
            if (this->Peek() == '>')
            {
                this->Next();
                this->AddToken(TOKEN_ARROW, "->", m_line);
            }
            else if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_MINUS_EQ, "-=", m_line);
            }
            else this->AddToken(TOKEN_MINUS, "-", m_line);
            break;
        case '%':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_PERCE_EQ, "%=", m_line);
            }
            else this->AddToken(TOKEN_PERCENT, "%", m_line);
            break;
        case '=':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_EQ, "==", m_line);
            }
            else this->AddToken(TOKEN_ASSIGN, "=", m_line);
            break;
        case '>':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_GTE, ">=", m_line);
            }
            else this->AddToken(TOKEN_GT, ">", m_line);
            break;
        case '<':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_LTE, "<=", m_line);
            }
            else this->AddToken(TOKEN_LT, "<", m_line);
            break;
        case '&':
            if (this->Peek() == '&')
            {
                this->Next();
                this->AddToken(TOKEN_AND_AND, "&&", m_line);
            }
            else this->AddToken(TOKEN_AND, "&", m_line);
            break;
        case '|':
            if (this->Peek() == '|')
            {
                this->Next();
                this->AddToken(TOKEN_OR_OR, "||", m_line);
            }
            else this->AddToken(TOKEN_OR, "|", m_line);
            break;
        case '^':
            this->AddToken(TOKEN_XOR, "^", m_line); break;
        case '!':
            if (this->Peek() == '=')
            {
                this->Next();
                this->AddToken(TOKEN_NOT_EQ, "!=", m_line);
            }
            else this->AddToken(TOKEN_NOT, "!", m_line);
            break;
        case ';':
            this->AddToken(TOKEN_SEMICOLON, ";", m_line); break;
        case ':':
            this->AddToken(TOKEN_COLON, ":", m_line); break;
        case '.':
            this->AddToken(TOKEN_DOT, ".", m_line); break;
        case ',':
            this->AddToken(TOKEN_COMMA, ",", m_line); break;
        case '(':
            this->AddToken(TOKEN_LPAREN, "(", m_line); break;
        case ')':
            this->AddToken(TOKEN_RPAREN, ")", m_line); break;
        case '{':
            this->AddToken(TOKEN_LBRACE, "{", m_line); break;
        case '}':
            this->AddToken(TOKEN_RBRACE, "}", m_line); break;
        case '[':
            this->AddToken(TOKEN_LBRACKET, "[", m_line); break;
        case ']':
            this->AddToken(TOKEN_RBRACKET, "]", m_line); break;
        case '\'':
            this->Next();
            if (this->Peek() != '\'')
            {
                // raise error
            }
            this->AddToken(TOKEN_CHAR, std::to_string(m_char), m_line);
            this->Next(); break;
        case '"':
            this->ReadString(); break;
        default:
            this->AddToken(TOKEN_ILLEGAL, std::to_string(m_char), m_line);
    }

    this->Next();
}

void Lexer::Next()
{
    size_t read_pos = m_pos + 1;

    if (read_pos >= m_content.length())
        m_char = '\0';
    else
        m_char = m_content[read_pos];

    ++m_pos;
}

char Lexer::Peek()
{
    size_t read_pos = m_pos + 1;

    if (read_pos >= m_content.length())
        return '\0';

    return m_content[read_pos];
}

void Lexer::AddToken(std::uint8_t type, const std::string& value, size_t line)
{
    m_tokens.push_back({
        .type=type,
        .value=value,
        .line=line
    });
}

// Skip repeats

void Lexer::SkipComment(bool multiline)
{
    if (multiline)
    {
        while ((m_char != '*' || this->Peek() != '/') && m_char != '\0')
        {
            this->Next();
        }

        this->Next();
    }
    else
    {
        while (m_char != '\n' && m_char != '\0')
        {
            this->Next();
        }
    }
}

void Lexer::SkipWhitespace()
{
    while (m_char == ' ' || m_char == '\t' || m_char == '\n' || m_char == '\r')
    {
        if (m_char ==  '\n') ++m_line;
        this->Next();
    }
}

// --- Reading specific token types ---

void Lexer::ReadIdentifier()
{
    size_t start = m_pos;
    this->Next();

    while (std::isalnum(m_char) || m_char == '_')
    {
        this->Next();
    }

    std::string identifier = m_content.substr(start, m_pos - start);
    // todo: check if identifier is a keyword

    this->AddToken(TOKEN_IDENTIFIER, identifier, m_line);
}

void Lexer::ReadString()
{
    size_t start = m_pos + 1;
    bool escaped = false;

    this->Next();

    while (m_char != '"' && m_char != '\0')
    {
        if (m_char == '\\')
        {
            escaped = true;
        }
        if (m_char == '\n') ++m_line;
        this->Next();
    }

    if (m_char != '"')
        return this->AddToken(TOKEN_ILLEGAL, "unterminated", m_line);

    std::string lex = m_content.substr(start, m_pos - start);
    this->AddToken(TOKEN_STRING, lex, m_line);

    this->Next();
}

void Lexer::ReadNumber()
{
    size_t start = m_pos;
    char starting_char = m_char;
    bool has_decimal = false;

    this->Next();

    while (std::isdigit(m_char) || (m_char == '.' && !has_decimal))
    {
        if (m_char == '.')
            has_decimal = true;

        this->Next();
    }

    std::string number = m_content.substr(start, m_pos - start);
    this->AddToken(TOKEN_NUMBER, number, m_line);
}
