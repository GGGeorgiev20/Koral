#pragma once

#include "Node.hpp"

class AssignmentExpression : public Node
{
public:
    DEFINE_NODE(AssignmentExpression, 1)

    AssignmentExpression(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::shared_ptr<Node> variable;
};