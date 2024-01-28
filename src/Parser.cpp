#include "Parser.hpp"

std::vector<std::shared_ptr<Node>> Parser::Parse()
{
    // AnalyzeSyntax();

    GenerateAST();

    return AST;
}

void Parser::AnalyzeSyntax()
{
    auto tokensLines = GetTokensLines();

    for (auto line : tokensLines)
    {
        size_t parenthesis = 0;
        size_t quotes = 0;

        for (size_t i = 0; i < line.size(); i++)
        {
            auto token = line[i];

            if (i + 1 < line.size())
            {
                auto nextTwo = std::vector<std::shared_ptr<Token>>(line.begin() + i, line.begin() + i + 2);

                SyntaxManager::CheckIfExpected(nextTwo);

                SyntaxManager::CheckIllegalRepeat(nextTwo);

                if (i + 2 < line.size())
                {
                    auto nextThree = std::vector<std::shared_ptr<Token>>(line.begin() + i, line.begin() + i + 3);

                    SyntaxManager::CheckIllegalRepeat(nextThree);
                }
            }

            if (token->GetValue() == "(" || token->GetValue() == ")")
                parenthesis++;
            else if (token->GetValue() == "\"" || token->GetValue() == "\'")
                quotes++;
        }

        if (parenthesis % 2 != 0)
            SYNTAX_ERROR("Missing opening or closing parenthesis", line[0]->GetLine());
        
        if (quotes % 2 != 0)
            SYNTAX_ERROR("Missing opening or closing quote", line[0]->GetLine());
    }
}   

void Parser::GenerateAST()
{
    auto tokensLines = GetTokensLines();

    for (auto line : tokensLines)
    {
        for (size_t i = 0; i < line.size() - 1; i++)
        {
            auto token = line[i];

            std::vector<std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Token>>, size_t& iterator)>> constructors =
            {
                NodeConstructor::CheckVariableDeclaration,
                NodeConstructor::CheckCallExpression,
                NodeConstructor::CheckAssignmentExpression,
                NodeConstructor::CheckBinaryExpression
            };

            std::vector<std::shared_ptr<Token>> lineOnwards(line.begin() + i, line.end()); 

            // TODO: Rework semicolons (need to be expected at end of expression, not line)
            if (TokenManager::GetValueByIndex(line, line.size() - 1) != ";")
                SYNTAX_ERROR("Expected semicolon at end of line", token->GetLine());

            if (token->GetValue() == ";")
                SYNTAX_ERROR("Unexpected semicolon", token->GetLine());

            for (auto NodeConstructor : constructors)
            {
                auto node = NodeConstructor(lineOnwards, i);

                if (node != nullptr)
                {
                    AST.push_back(node);
                    break;
                }
            }
        }
    }
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

            currentLine = token->GetLine();
        }

        line.push_back(token);
    }

    lines.push_back(line);

    return lines;
}

template <typename N>
std::shared_ptr<Node> Parser::AddNode(std::vector<std::any> attributes)
{
    return NodeManager::CreateNode<N>(attributes);
}