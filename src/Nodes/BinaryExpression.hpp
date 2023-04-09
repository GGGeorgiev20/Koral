#pragma once

#include "Node.hpp"

enum class Operator
{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

class BinaryExpression : public Node
{
public:
    DEFINE_NODE(BinaryExpression)

    BinaryExpression(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::any left;
    std::any right;
    Operator op;

    std::shared_ptr<Node> next;

    size_t attributesCount = 4;
};