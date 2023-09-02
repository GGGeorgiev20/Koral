#pragma once

#include "Node.hpp"

class Literal : public Node
{
public:
    DEFINE_NODE(Literal, 2)

    Literal(const std::vector<std::any>& attributes);

    void Execute() override;

    std::vector<std::any> GetAttributes() override;

private:
    std::any value;
    std::string type;
};