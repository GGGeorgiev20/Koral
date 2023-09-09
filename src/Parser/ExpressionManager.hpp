#pragma once

#include "../Util/ErrorManager.hpp"
#include "../Nodes/NodeManager.hpp"

#include "../Token.hpp"

#include <unordered_map>
#include <algorithm>

namespace ExpressionManager
{
    std::shared_ptr<Node> GetBinaryExpression(std::vector<std::shared_ptr<Token>>& expression);

    std::vector<std::shared_ptr<Token>> ConvertToPostfix(std::vector<std::shared_ptr<Token>>& expression);
};