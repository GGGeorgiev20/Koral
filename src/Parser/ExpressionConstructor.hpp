#pragma once

#include <unordered_map>
#include <algorithm>

#include "../Token.hpp"

#include "../Logs/ErrorManager.hpp"
#include "../Nodes/NodeManager.hpp"

namespace ExpressionConstructor
{
    std::shared_ptr<Node> GetBinaryExpression(std::vector<std::shared_ptr<Token>> expression);

    std::shared_ptr<Node> ConstructExpression(std::vector<std::shared_ptr<Token>> expression);

    std::vector<std::shared_ptr<Token>> ConvertToPostfix(std::vector<std::shared_ptr<Token>> expression);

    void ProcessToken(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Node>>& stack);

    void ProcessOperator(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Token>>& stack, std::vector<std::shared_ptr<Token>>& postfix);

    void ProcessPunctuation(std::shared_ptr<Token> token, std::vector<std::shared_ptr<Token>>& stack, std::vector<std::shared_ptr<Token>>& postfix);

    void EmptyStack(std::vector<std::shared_ptr<Token>>& stack, std::vector<std::shared_ptr<Token>>& postfix);
};