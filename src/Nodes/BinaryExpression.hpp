#pragma once

#include "Node.hpp"
#include "Literal.hpp"

enum class Operator
{
    Add,
    Subtract,
    Multiply,
    Divide
};

class BinaryExpression : public Node
{
public:
    DEFINE_NODE(BinaryExpression, 3)

    BinaryExpression(const std::vector<std::any>& attributes);

    void Execute() override;

    Literal GetResult();

    std::vector<std::any> GetAttributes() override;

private:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Operator op;

    Literal result;
};