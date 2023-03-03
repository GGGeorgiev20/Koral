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

    void ExecuteNull();

    void ExecuteLiteral();

    void ExecuteBinaryExpression();

    std::vector<std::any> GetAttributes() override;

private:
    std::string type;
    std::string identifier;
    std::shared_ptr<Node> expression;
};