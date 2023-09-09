#include "./ExpressionManager.hpp"

namespace ExpressionManager
{
    const std::unordered_map<char, int> precedence = {
        {'*', 1},
        {'/', 1},
        {'%', 1},
        {'+', 2},
        {'-', 2}
    };

    std::shared_ptr<Node> GetBinaryExpression(std::vector<std::shared_ptr<Token>>& expression)
    {
        auto postfix = ConvertToPostfix(expression);

        printf("Postfix: ");
        for (auto& token : postfix)
        {
            printf("%s", token->GetValue().c_str());
        }
        printf("\n");

        // std::stack<std::shared_ptr<Node>> stack;

        return nullptr;
    }

    std::vector<std::shared_ptr<Token>> ConvertToPostfix(std::vector<std::shared_ptr<Token>>& expression)
    {
        std::vector<std::shared_ptr<Token>> postfix;

        // Stack used to store operators
        std::vector<std::shared_ptr<Token>> stack;

        for (auto& token : expression)
        {
            if (token->GetType() == "Number" || token->GetType() == "String" || token->GetType() == "Identifier")
            {
                postfix.push_back(token);
            }
            else if (token->GetType() == "Operator")
            {
                char op = token->GetValue()[0];

                // Get the uppermost operator in the stack
                char top;

                for (int i = stack.size() - 1; i >= 0; i--)
                {
                    if (stack[i]->GetType() == "Operator")
                    {
                        top = stack[i]->GetValue()[0];
                        break;
                    }
                }

                if (stack.empty())
                    stack.push_back(token);

                else if (precedence.at(op) < precedence.at(top))
                    stack.push_back(token);

                else if (op == top)
                    stack.push_back(token);

                else
                {
                    // Pop all operators with higher or equal precedence
                    while (!stack.empty() && precedence.at(op) >= precedence.at(top))
                    {
                        if (stack.back()->GetValue() == "(" || stack.back()->GetValue() == ")")
                            break;

                        postfix.push_back(stack.back());
                        stack.pop_back();
                    }

                    stack.push_back(token);
                }
            }
            else
            {
                if (token->GetValue() == "(")
                {
                    stack.push_back(token);
                }
                else if (token->GetValue() == ")")
                {
                    while (!stack.empty() && stack.back()->GetValue() != "(")
                    {
                        postfix.push_back(stack.back());
                        stack.pop_back();
                    }

                    if (stack.empty())
                        ErrorManager::GetInstance()->RuntimeError("Missing opening parentheses", token->GetLine());
                    else
                        stack.pop_back();
                }
            }
        }

        while (!stack.empty())
        {
            if (stack.back()->GetValue() == "(" || stack.back()->GetValue() == ")")
                ErrorManager::GetInstance()->RuntimeError("Missing closing parentheses", stack.back()->GetLine());

            postfix.push_back(stack.back());
            stack.pop_back();
        }

        return postfix;
    }
};