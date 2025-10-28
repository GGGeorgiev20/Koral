#pragma once

#include <string>

struct Node
{
    std::string node; // debugging purposes
    virtual ~Node() = default;
};

// #define SETUP_NODE(name) std::string name = "name";
