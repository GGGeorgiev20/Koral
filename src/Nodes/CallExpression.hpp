#pragma once

#include "Node.hpp"

class CallExpression : public Node
{
public:
    DEFINE_NODE(CallExpression)

    CallExpression(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::string identifier;
    std::vector<std::shared_ptr<Node>> arguments;

    size_t attributesCount = 2;
};