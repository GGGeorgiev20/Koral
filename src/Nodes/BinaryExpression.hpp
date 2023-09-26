#pragma once

#include "Node.hpp"

class BinaryExpression : public Node
{
public:
    DEFINE_NODE(BinaryExpression, 3)

    BinaryExpression(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::string op;
};