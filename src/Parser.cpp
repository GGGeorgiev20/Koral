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
        size_t paranthesis = 0;
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
        for (size_t i = 0; i < line.size() - 1; i++)
        {
            auto token = line[i];

            // Check for semicolon at the end of the line
            if (TokenManager::GetValueByIndex(line, line.size() - 1) != ";")
                SYNTAX_ERROR("Expected semicolon at end of line", token->GetLine());

            if (token->GetValue() == ";")
                SYNTAX_ERROR("Unexpected semicolon", token->GetLine());

            // Variable declaration
            if (token->GetType() == "Type")
            {
                std::string type = token->GetValue();

                std::string identifier = TokenManager::GetValueByIndex(line, i + 1);

                if (identifier == ";" || identifier == "Null")
                    SYNTAX_ERROR("Expected identifier at variable declaration", token->GetLine());
                
                if (!SyntaxManager::IsVariableNameValid(identifier))
                    SYNTAX_ERROR("Invalid identifier at variable declaration", token->GetLine());

                auto node = AddNode<VariableDeclaration>({ type, identifier });

                AST.push_back(node);

                continue;
            }

            // Call expression
            if (token->GetType() == "Identifier")
            {
                std::string identifier = token->GetValue();

                if (TokenManager::GetValueByIndex(line, i + 1) == "(")
                {
                    std::vector<std::shared_ptr<Node>> arguments;
                    std::vector<std::shared_ptr<Token>> currentArgument;

                    std::string value;

                    i += 2;
                    while (true)
                    {
                        value = TokenManager::GetValueByIndex(line, i);
                        
                        if (value == ";" || value == "Null")
                            SYNTAX_ERROR("Expected end at call expression", token->GetLine());
                        
                        if (value == ")")
                        {
                            if (currentArgument.size() != 0)
                            {
                                auto expression = ExpressionConstructor::GetBinaryExpression(currentArgument);

                                arguments.push_back(expression);

                                currentArgument.clear();
                            }

                            break;
                        }

                        if (value == ",")
                        {
                            // Check if the current argument is a CallExpression

                            if (currentArgument.size() == 0)
                                SYNTAX_ERROR("Expected value at call expression", token->GetLine());

                            if (!SyntaxManager::IsExpressionValid(currentArgument))
                                SYNTAX_ERROR("Expression is not valid", token->GetLine());

                            auto expression = ExpressionConstructor::GetBinaryExpression(currentArgument);

                            arguments.push_back(expression);

                            currentArgument.clear();
                        }
                        else
                        {
                            currentArgument.push_back(line[i]);
                        }

                        i++;
                    }

                    std::shared_ptr<Node> node;

                    node = AddNode<CallExpression>({ identifier, arguments });

                    AST.push_back(node);

                    continue;
                }
            }

            // Assignment expression
            if (token->GetType() == "Identifier")
            {
                std::string identifier = token->GetValue();

                if (TokenManager::GetValueByIndex(line, i + 1) == "=")
                {
                    i++;

                    std::shared_ptr<Node> variable = AddNode<VariableReference>({ identifier });
                    std::shared_ptr<Node> node = AddNode<AssignmentExpression>({ variable });

                    AST.push_back(node);

                    continue;
                }
            }

            // Binary expression
            if (token->GetType() == "Identifier" || token->GetType() == "Number" || token->GetType() == "String")
            {
                std::vector<std::shared_ptr<Token>> expression;

                expression.push_back(token);

                std::string value;

                i++;
                while (true)
                {
                    value = TokenManager::GetValueByIndex(line, i);

                    if (value == "Null")
                        SYNTAX_ERROR("Expected end of expression", token->GetLine());

                    if (value == ";")
                        break;

                    expression.push_back(line[i]);

                    i++;
                }

                if (!SyntaxManager::IsExpressionValid(expression))
                    SYNTAX_ERROR("Expression is not valid", token->GetLine());

                auto node = ExpressionConstructor::GetBinaryExpression(expression);

                AST.push_back(node);

                continue;
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
std::shared_ptr<Node> Parser::AddNode(const std::vector<std::any>& attributes)
{
    return NodeManager::CreateNode<N>(attributes);
}