#pragma once

#include "Common/Nodes/Node.hpp"
#include "Common/Nodes/Semantics/Rule.hpp"

#include <vector>

struct SemanticsSection : public Node
{
    std::string node = "SemanticsSection";

    std::vector<SemanticsRule> rules;
};
