#include "Lexer.hpp"

Token::Token(std::string value, size_t line)
{
    this->value = value;
    this->line = line;
}

std::vector<std::shared_ptr<Token>> Lexer::Lex()
{
    Scan();
    Evaluate();

    PostProcess();

    return tokens;
}

void Lexer::Scan()
{
    std::vector<std::string> lines = ReadLines();
    bool inString = false;

    for (size_t i = 0; i < lines.size(); i++)
    {
        std::string line = lines[i];
        std::string lexeme = "";

        for (auto character : line)
        {
            ProccessCharacter(character, lexeme, inString, i);
        }

        if (lexeme != "")
        {
            AddToken(lexeme, i);
        }
    }
}

void Lexer::ProccessCharacter(char character, std::string& lexeme, bool& inString, size_t line)
{
    if (character == '\"' || character == '\'')
    {
        inString = !inString;
    }

    if (inString)
    {
        lexeme += character;
        return;
    }

    if (character == ' ')
    {
        if (lexeme != "")
        {
            AddToken(lexeme, line);
        }

        return;
    }
    
    if (std::find(punctuation.begin(), punctuation.end(), character) != punctuation.end() ||
        std::find(operators.begin(), operators.end(), character) != operators.end())
    {
        if (lexeme != "")
        {
            AddToken(lexeme, line);
        }

        lexeme += character;
        AddToken(lexeme, line);

        return;
    }

    lexeme += character;
}

void Lexer::Evaluate()
{
    for (auto& token : tokens)
    {
        std::string type = DetermineType(token->GetValue());
        token->SetType(type);
    }
}

void Lexer::PostProcess()
{
    for (size_t i = 1; i < tokens.size() - 1; i++)
    {
        auto& previousToken = tokens[i - 1];
        auto& token = tokens[i];
        auto& nextToken = tokens[i + 1];

        std::vector<std::shared_ptr<Token>> tokensToCheck = { previousToken, token, nextToken };

        std::vector<std::string> unary = { "Operator", "Operator", "Number" };
        std::vector<std::string> floating = { "Number", "Punctuation", "Number" };

        if (AreForwarded(tokensToCheck, unary))
        {
            if (token->GetValue() == "-" || token->GetValue() == "+")
            {
                std::string value = token->GetValue() + nextToken->GetValue();
                nextToken->SetValue(value);

                tokens.erase(tokens.begin() + i);
            }
        }

        if (AreForwarded(tokensToCheck, floating))
        {
            if (token->GetValue() == ".")
            {
                std::string value = previousToken->GetValue() + token->GetValue() + nextToken->GetValue();
                nextToken->SetValue(value);

                tokens.erase(tokens.begin() + i);
                tokens.erase(tokens.begin() + i - 1);
            }
        }
    }
}

std::string Lexer::DetermineType(std::string lexeme)
{
    if (std::find(keywords.begin(), keywords.end(), lexeme) != keywords.end())
        return "Keyword";

    if (std::find(types.begin(), types.end(), lexeme) != types.end())
        return "Type";

    if (std::find(operators.begin(), operators.end(), lexeme[0]) != operators.end())
        return "Operator";
    
    if (std::find(punctuation.begin(), punctuation.end(), lexeme[0]) != punctuation.end())
        return "Punctuation";
    
    if (lexeme[0] == '"' || lexeme[0] == '\'')
        return "String";
    
    try
    {
        std::stoi(lexeme);
        return "Number";
    }
    catch (std::invalid_argument const&)
    {
        return "Identifier";
    }

    return "Unknown";
}

std::vector<std::string> Lexer::ReadLines()
{
    std::vector<std::string> lines;
    std::string line;

    for (size_t i = 0; i < content.length(); i++)
    {
        if (content[i] != '\n')
        {
            line += content[i];
            continue;
        }

        lines.push_back(line);
        line = "";
    }

    lines.push_back(line);

    return lines;
}

bool Lexer::AreForwarded(std::vector<std::shared_ptr<Token>> tokens, std::vector<std::string> expected)
{
    if (tokens.size() != expected.size())
    {
        return false;
    }
    
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i]->GetType() != expected[i])
        {
            return false;
        }
    }

    return true;
}

void Lexer::AddToken(std::string& lexeme, size_t line)
{
    auto token = std::make_shared<Token>(lexeme, line);
    
    tokens.push_back(token);

    lexeme = "";
}