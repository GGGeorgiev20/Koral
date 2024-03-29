#pragma once

#include <algorithm>

#include "TokenManager.hpp"
#include "SyntaxManager.hpp"
#include "ExpressionConstructor.hpp"

#include "../Token.hpp"

#include "../Logs/ErrorManager.hpp"
#include "../Nodes/NodeManager.hpp"

namespace NodeConstructor
{
    std::shared_ptr<Node> CheckVariableDeclaration(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator);

    std::shared_ptr<Node> CheckCallExpression(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator);

    std::shared_ptr<Node> CheckAssignmentExpression(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator);
    
    std::shared_ptr<Node> CheckBinaryExpression(std::vector<std::shared_ptr<Token>> tokens, size_t& iterator);
};