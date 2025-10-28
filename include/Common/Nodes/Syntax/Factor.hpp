#pragma once

#include "Common/Nodes/Node.hpp"

#include <string>
#include <vector>
#include <cstdint>

enum Type : uint8_t
{
    TERMINAL,
    IDENTIFIER,
    REGEX,
    GROUP,
    OPTIONAL,
    REPEAT
};

struct Factor : public Node
{
    std::string node = "Factor";

    Type type;

    std::string value;
    std::vector<Factor> nested;

    char occurence;
};
