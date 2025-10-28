#pragma once

#include "Common/Nodes/Node.hpp"
#include "Common/Nodes/Syntax/Factor.hpp"

#include <string>
#include <vector>

struct SyntaxRule : public Node
{
    std::string node = "SyntaxRule";

    std::string non_terminal;
    std::string extends;
    std::vector<Factor> factors;
};
