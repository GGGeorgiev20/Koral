#pragma once

#include "Common/Nodes/Node.hpp"

#include <string>
#include <vector>

struct Property
{
    std::string key;
    std::string value;
};

struct SemanticsRule : public Node
{
    std::string node = "SemanticsRule";

    std::string non_terminal;
    std::vector<Property> property;
};
