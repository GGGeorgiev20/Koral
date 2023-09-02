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

    // This variable receives a value when an assignment expression is found and an expression is expected
    std::shared_ptr<Node> expectingExpression = nullptr;

    for (auto line : tokensLines)
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            auto token = line[i];
            std::vector<std::any> attributes;

            // Variable declaration
            if (token->GetType() == "Type")
            {
                std::string type = token->GetValue();

                std::string identifier = TokenManager::GetValueByIndex(line, i + 1);

                if (identifier == "Null")
                    SYNTAX_ERROR("Expected identifier at variable declaration", token->GetLine());
                
                if (!SyntaxManager::IsVariableNameValid(identifier))
                    SYNTAX_ERROR("Invalid identifier at variable declaration", token->GetLine());

                attributes = { type, identifier };

                auto node = AddNode<VariableDeclaration>(attributes);

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
                        
                        if (value == "Null")
                            SYNTAX_ERROR("Expected end at call expression", token->GetLine());
                        
                        if (value == ")")
                        {
                            if (currentArgument.size() != 0)
                            {
                                auto expression = GetBinaryExpression(currentArgument);

                                arguments.push_back(expression);

                                currentArgument.clear();
                            }

                            break;
                        }

                        if (value == ",")
                        {
                            if (currentArgument.size() == 0)
                                SYNTAX_ERROR("Expected value at call expression", token->GetLine());

                            auto expression = GetBinaryExpression(currentArgument);

                            arguments.push_back(expression);

                            currentArgument.clear();
                        }
                        else
                        {
                            currentArgument.push_back(line[i]);
                        }

                        i++;
                    }

                    attributes = { identifier, arguments };

                    auto node = AddNode<CallExpression>(attributes);

                    // Check if an expression is expected
                    if (expectingExpression != nullptr)
                    {
                        attributes = { expectingExpression, node };

                        node = AddNode<AssignmentExpression>(attributes);

                        AST.push_back(node);

                        expectingExpression = nullptr;

                        continue;
                    }

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
                    // Gives value to the variable so the code knows that an expression is expected
                    expectingExpression = AddNode<VariableReference>({ identifier });

                    i++;

                    continue;
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

std::shared_ptr<Node> Parser::GetBinaryExpression(std::vector<std::shared_ptr<Token>>& tokens)
{
    std::shared_ptr<Node> node;

    if (tokens.size() == 1)
    {
        if (tokens[0]->GetType() == "Identifier")
            node = AddNode<VariableReference>({ tokens[0]->GetValue() });
        else
            node = AddNode<Literal>({ tokens[0]->GetValue(), tokens[0]->GetType() });
    }
    else
        node = AddNode<BinaryExpression>({ tokens[1]->GetValue(), tokens[0]->GetValue(), tokens[2]->GetValue() });
    
    return node;
}

template <typename N>
std::shared_ptr<Node> Parser::AddNode(const std::vector<std::any>& attributes)
{
    return NodeManager::CreateNode<N>(attributes);
}