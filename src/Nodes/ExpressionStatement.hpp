#pragma once

#include "Node.hpp"

class ExpressionStatement : public Node
{
public:
    DEFINE_NODE(ExpressionStatement)

    ExpressionStatement(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::string identifier;
    std::shared_ptr<Node> expression;
};