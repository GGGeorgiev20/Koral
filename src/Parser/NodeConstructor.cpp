#include "NodeConstructor.hpp"

namespace NodeConstructor
{
    std::shared_ptr<Node> CheckVariableDeclaration(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator)
    {
        auto token = tokens[0];

        if (token->GetType() != "Type")
            return nullptr;

        // Casting it to void (does nothing), so that the compiler doesn't give an unused warning
        (void)iterator;
        
        std::string type = token->GetValue();

        std::string identifier = TokenManager::GetValueByIndex(tokens, 1);

        if (identifier == ";" || identifier == "Null")
            SYNTAX_ERROR("Expected identifier at variable declaration", token->GetLine());
        
        if (!SyntaxManager::IsVariableNameValid(identifier))
            SYNTAX_ERROR("Invalid identifier at variable declaration", token->GetLine());

        auto node = NodeManager::CreateNode<VariableDeclaration>({ type, identifier });

        return node;
    }

    std::shared_ptr<Node> CheckCallExpression(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator)
    {
        auto token = tokens[0];
        auto next = tokens[1];

        if (token->GetType() != "Identifier")
            return nullptr;
        
        if (next->GetValue() != "(")
            return nullptr;
        
        std::string identifier = token->GetValue();

        std::vector<std::shared_ptr<Node>> arguments;
        std::vector<std::shared_ptr<Token>> currentArgument;

        std::string value;

        // TODO: Call expressions can't be passed as a parameter to a function call

        size_t localIterator = 2;
        
        while (true)
        {
            value = TokenManager::GetValueByIndex(tokens, localIterator);
            
            if (value == ";" || value == "Null")
                SYNTAX_ERROR(CALL_EXPECTED_END, token->GetLine());
            
            if (value == ")")
            {
                if (currentArgument.size() != 0)
                {
                    if (!SyntaxManager::IsExpressionValid(currentArgument))
                        SYNTAX_ERROR(EXPRESSION_NOT_VALID, token->GetLine());

                    auto expression = ExpressionConstructor::GetBinaryExpression(currentArgument);

                    arguments.push_back(expression);

                    currentArgument.clear();
                }

                break;
            }

            if (value == ",")
            {
                if (currentArgument.size() == 0)
                    SYNTAX_ERROR(CALL_EXPECTED_VALUE, token->GetLine());

                if (!SyntaxManager::IsExpressionValid(currentArgument))
                    SYNTAX_ERROR(EXPRESSION_NOT_VALID, token->GetLine());

                auto expression = ExpressionConstructor::GetBinaryExpression(currentArgument);

                arguments.push_back(expression);

                currentArgument.clear();
            }
            else
            {
                currentArgument.push_back(tokens[localIterator]);
            }

            localIterator++;
        }

        iterator += localIterator;

        auto node = NodeManager::CreateNode<CallExpression>({ identifier, arguments });

        return node;
    }

    std::shared_ptr<Node> CheckAssignmentExpression(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator)
    {
        auto token = tokens[0];
        auto next = tokens[1];

        if (token->GetType() != "Identifier")
            return nullptr;

        if (next->GetValue() != "=")
            return nullptr;

        iterator++;

        std::string identifier = token->GetValue();

        std::shared_ptr<Node> variable = NodeManager::CreateNode<VariableReference>({ identifier });

        auto node = NodeManager::CreateNode<AssignmentExpression>({ variable });

        return node;
    }

    std::shared_ptr<Node> CheckBinaryExpression(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator)
    {
        // TODO: Whole binary expression check needs to be remade
        //       Braces aren't allowed at beginning and end

        auto token = tokens[0];

        if (token->GetType() != "Identifier" &&
            token->GetType() != "Number" &&
            token->GetType() != "String")
            return nullptr;
        
        std::vector<std::shared_ptr<Token>> expression;

        expression.push_back(token);

        std::string value;

        size_t localIterator = 1;

        while (true)
        {
            value = TokenManager::GetValueByIndex(tokens, localIterator);

            if (value == "Null")
                SYNTAX_ERROR(EXPRESSION_EXPECTED_END, token->GetLine());

            if (value == ";")
                break;

            expression.push_back(tokens[localIterator]);

            localIterator++;
        }

        if (!SyntaxManager::IsExpressionValid(expression))
            SYNTAX_ERROR(EXPRESSION_NOT_VALID, token->GetLine());

        iterator += localIterator;

        // TODO: When constructing an expression, function calls are also passed as parameters
        //       When a function call is being processed, it raises an error
        //       They need to be made acceptable as parameters
        auto node = ExpressionConstructor::GetBinaryExpression(expression);

        return node;
    }

    // TODO: Implement all remaining nodes
};