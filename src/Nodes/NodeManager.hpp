#pragma once

#include "AssignmentExpression.hpp"
#include "BinaryExpression.hpp"
#include "CallExpression.hpp"
#include "Literal.hpp"
#include "VariableDeclaration.hpp"
#include "VariableReference.hpp"

namespace NodeManager
{
    template <typename N>
    static std::shared_ptr<N> CreateNode(std::vector<std::any> attributes)
    {
        static_assert(std::is_base_of<Node, N>::value, "N must inherit from Node");
        return std::make_shared<N>(attributes);
    }
}