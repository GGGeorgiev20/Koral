#include "Parser.hpp"

std::vector<std::shared_ptr<Node>> Parser::Parse()
{
    AnalyzeSyntax();

    GenerateAST();

    return AST;
}

void Parser::AnalyzeSyntax()
{
    auto tokensLines = GetTokensLines();

    for (auto line : tokensLines)
    {
        size_t paranthesis = 0;
        size_t quotes = 0;

        for (size_t i = 0; i < line.size(); i++)
        {
            auto token = line[i];

            if (i + 1 < line.size())
            {
                auto nextTwo = std::vector<std::shared_ptr<Token>>(line.begin() + i, line.begin() + i + 2);

                CheckIfExpected(nextTwo);

                CheckIllegalRepeat(nextTwo);

                if (i + 2 < line.size())
                {
                    auto nextThree = std::vector<std::shared_ptr<Token>>(line.begin() + i, line.begin() + i + 3);

                    CheckIllegalRepeat(nextThree);
                }
            }

            if (token->GetType() == "Type" || token->GetType() == "Array") // TO DO: Arrays
            {
                if (GetTypeByIndex(line, i + 1) != "Identifier")
                {
                    SYNTAX_ERROR("Expected identifier at variable declaration", token->GetLine());
                }
                else
                {
                    if (GetValueByIndex(line, i + 2) != "=" && GetValueByIndex(line, i + 2) != "Null")
                    {
                        SYNTAX_ERROR("Expected assignment operator at variable declaration", token->GetLine());
                    }
                    else if (GetValueByIndex(line, i + 2) == "=")
                    {
                        if (GetValueByIndex(line, i + 3) == "Null")
                            SYNTAX_ERROR("Expected value at variable declaration", token->GetLine());
                    }
                }
            }

            if (token->GetValue() == "(" || token->GetValue() == ")")
                paranthesis++;
            else if (token->GetValue() == "\"" || token->GetValue() == "\'")
                quotes++;
        }

        if (paranthesis % 2 != 0)
            SYNTAX_ERROR("Missing opening or closing paranthesis", line[0]->GetLine());
        
        if (quotes % 2 != 0)
            SYNTAX_ERROR("Missing opening or closing quote", line[0]->GetLine());
    }
}   

void Parser::GenerateAST()
{
    auto tokensLines = GetTokensLines();

    for (auto line : tokensLines)
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            auto token = line[i];
            std::vector<std::any> attributes;

            if (token->GetType() == "Type")
            {
                std::string type = token->GetValue();
                std::string identifier = line[i + 1]->GetValue();

                if (GetValueByIndex(line, i + 3) == "Null")
                    attributes = { type, identifier, nullptr };
                else
                {
                    auto tokens = std::vector<std::shared_ptr<Token>>(line.begin() + i + 3, line.end());

                    auto expression = GetBinaryExpression(tokens);

                    attributes = { type, identifier, expression };
                }

                auto node = AddNode<VariableDeclaration>(attributes);

                AST.push_back(node);
            }
        }
    }
}

template <typename N>
std::shared_ptr<Node> Parser::AddNode(const std::vector<std::any>& attributes)
{
    return NodeManager::CreateNode<N>(attributes);
}

std::vector<std::vector<std::shared_ptr<Token>>> Parser::GetTokensLines()
{
    std::vector<std::vector<std::shared_ptr<Token>>> lines;
    std::vector<std::shared_ptr<Token>> line;

    size_t currentLine = 0;

    for (auto token : tokens)
    {
        if (token->GetLine() != currentLine)
        {
            lines.push_back(line);
            line.clear();

            currentLine++;
        }

        line.push_back(token);
    }

    lines.push_back(line);

    return lines;
}

std::shared_ptr<Node> Parser::GetBinaryExpression(std::vector<std::shared_ptr<Token>>& tokens)
{
    std::shared_ptr<Node> node;

    if (tokens.size() == 1)
        node = AddNode<Literal>({ tokens[0]->GetValue() });
    
    return node;
}

void Parser::CheckIllegalRepeat(std::vector<std::shared_ptr<Token>>& tokens)
{
    std::string type = tokens[0]->GetType();

    if (std::find(illegalRepeats.begin(), illegalRepeats.end(), type) == illegalRepeats.end() && tokens.size() == 2)
        return;

    for (auto token : tokens)
    {
        if (token->GetType() != type)
            return;
    }

    std::transform(type.begin(), type.end(), type.begin(), ::tolower);

    std::string message = "Unexpected " + type;
    size_t line = tokens[0]->GetLine();

    SYNTAX_ERROR(message, line);
}

void Parser::CheckIfExpected(std::vector<std::shared_ptr<Token>>& tokens)
{
    std::string type = tokens[0]->GetType();
    std::string nextType = tokens[1]->GetType();

    size_t index = std::find(indexes.begin(), indexes.end(), type) - indexes.begin();

    if (index < expectedAfter.size())
    {
        if (std::find(expectedAfter[index].begin(), expectedAfter[index].end(), nextType) == expectedAfter[index].end())
        {
            std::transform(type.begin(), type.end(), type.begin(), ::tolower);
            std::transform(nextType.begin(), nextType.end(), nextType.begin(), ::tolower);

            std::string message = "Unexpected " + nextType + " after " + type;
            size_t line = tokens[0]->GetLine();

            SYNTAX_ERROR(message, line);
        }
    }
}

std::string Parser::GetTypeByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index)
{
    if (index < tokens.size())
        return tokens[index]->GetType();
    else
        return "Null";
}

std::string Parser::GetValueByIndex(const std::vector<std::shared_ptr<Token>>& tokens, const size_t& index)
{
    if (index < tokens.size())
        return tokens[index]->GetValue();
    else
        return "Null";
}