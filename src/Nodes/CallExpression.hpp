#pragma once

#include "Node.hpp"

class CallExpression : public Node
{
public:
    DEFINE_NODE(CallExpression, 2)

    CallExpression(std::vector<std::any> attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::string identifier;
    std::vector<std::shared_ptr<Node>> arguments;
};