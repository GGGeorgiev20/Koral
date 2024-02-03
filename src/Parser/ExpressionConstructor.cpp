#include "ExpressionConstructor.hpp"

namespace ExpressionConstructor
{
    const std::unordered_map<char, int> precedence = {
        {'*', 1},
        {'/', 1},
        {'%', 1},
        {'+', 2},
        {'-', 2}
    };

    std::shared_ptr<Node> GetBinaryExpression(std::vector<std::shared_ptr<Token>> expression)
    {
        auto postfix = ConvertToPostfix(expression);

        auto node = ConstructExpression(postfix);

        return node;
    }

    std::shared_ptr<Node> ConstructExpression(std::vector<std::shared_ptr<Token>> expression)
    {
        std::vector<std::shared_ptr<Node>> stack;

        for (auto& token : expression)
        {
            ProcessToken(token, stack);
        }

        auto node = stack.back();

        return node;
    }

    void ProcessToken(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>>& stack)
    {
        if (token->GetType() == "Number" || token->GetType() == "String")
        {
            auto node = NodeManager::CreateNode<Literal>({ token->GetValue(), token->GetType() });

            stack.push_back(node);
        }
        else if (token->GetType() == "Identifier")
        {
            auto node = NodeManager::CreateNode<VariableReference>({ token->GetValue() });

            stack.push_back(node);
        }
        else if (token->GetType() == "Operator")
        {
            auto right = stack.back();
            stack.pop_back();

            auto left = stack.back();
            stack.pop_back();

            auto node = NodeManager::CreateNode<BinaryExpression>({ left, right, token->GetValue() });

            stack.push_back(node);
        }
    }

    std::vector<std::shared_ptr<Token>> ConvertToPostfix(std::vector<std::shared_ptr<Token>> expression)
    {
        std::vector<std::shared_ptr<Token>> postfix;

        // Stack used to store operators (vector is used, so searching is possible)
        std::vector<std::shared_ptr<Token>> stack;

        for (auto& token : expression)
        {
            if (token->GetType() == "Number" || token->GetType() == "String" || token->GetType() == "Identifier")
            {
                postfix.push_back(token);
            }
            else if (token->GetType() == "Operator")
            {
                ProcessOperator(token, stack, postfix);
            }
            else
            {
                ProcessPunctuation(token, stack, postfix);
            }
        }

        EmptyStack(stack, postfix);

        return postfix;
    }

    void ProcessOperator(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Token>>& stack, std::vector<std::shared_ptr<Token>>& postfix)
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
        {
            stack.push_back(token);
        }

        else if (precedence.at(op) < precedence.at(top))
        {
            stack.push_back(token);
        }

        else if (op == top)
        {
            stack.push_back(token);
        }

        else
        {
            // Pop all operators with higher or equal precedence
            while (!stack.empty() && precedence.at(op) >= precedence.at(top))
            {
                if (stack.back()->GetValue() == "(" || stack.back()->GetValue() == ")")
                {
                    break;
                }

                postfix.push_back(stack.back());
                stack.pop_back();
            }

            stack.push_back(token);
        }
    }

    void ProcessPunctuation(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Token>>& stack, std::vector<std::shared_ptr<Token>>& postfix)
    {
        if (token->GetValue() == "(")
        {
            stack.push_back(token);
            return;
        }

        if (token->GetValue() != ")")
        {
            return;
        }

        while (!stack.empty() && stack.back()->GetValue() != "(")
        {
            postfix.push_back(stack.back());
            stack.pop_back();
        }

        if (stack.empty())
        {
            ErrorManager::GetInstance()->RuntimeError(MISSING_OPENING_PARENTHESIS, token->GetLine());
        }
        else
        {
            stack.pop_back();
        }
    }

    void EmptyStack(std::vector<std::shared_ptr<Token>>& stack, std::vector<std::shared_ptr<Token>>& postfix)
    {
        while (!stack.empty())
        {
            if (stack.back()->GetValue() == "(" || stack.back()->GetValue() == ")")
            {
                ErrorManager::GetInstance()->RuntimeError(MISSING_CLOSING_PARENTHESIS, stack.back()->GetLine());
            }

            postfix.push_back(stack.back());
            stack.pop_back();
        }
    }
};