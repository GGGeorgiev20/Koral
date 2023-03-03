#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include <typeinfo>
#include <any>

class Node
{
public:
    ~Node() = default;

    virtual void Execute() = 0;

    virtual std::vector<std::any> GetAttributes() = 0;

    virtual std::string GetType() = 0;
};

#define DEFINE_NODE(name) std::string GetType() override { return #name; }