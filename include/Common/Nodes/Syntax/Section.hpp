#pragma once

#include "Common/Nodes/Node.hpp"
#include "Common/Nodes/Syntax/Rule.hpp"

#include <vector>

struct SyntaxSection : public Node
{
    std::string node = "SyntaxSection";

    std::vector<SyntaxRule> rules;
};
