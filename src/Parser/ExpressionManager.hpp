#pragma once

#include "../Nodes/Node.hpp"

class ExpressionManager
{
public:
    std::vector<std::shared_ptr<Node>> GetArguments();

private:
    const std::vector<char> priority = { '(', ')', '*', '/', '+', '-' };
};