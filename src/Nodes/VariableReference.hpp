#pragma once

#include "Node.hpp"

class VariableReference : public Node
{
public:
    DEFINE_NODE(VariableReference, 1)

    VariableReference(std::vector<std::any> attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::string name;
};