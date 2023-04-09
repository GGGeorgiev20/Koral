#pragma once

#include "Node.hpp"
#include "Literal.hpp"
#include "BinaryExpression.hpp"

#include "../Variables/VariableManager.hpp"

class VariableDeclaration : public Node
{
public:
    DEFINE_NODE(VariableDeclaration)

    VariableDeclaration(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::string type;
    std::string identifier;

    size_t attributesCount = 2;
};