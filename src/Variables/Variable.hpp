#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <any>

class Variable
{
public:
    Variable(std::string type, std::string identifier, std::any value)
    {
        this->type = type;
        this->identifier = identifier;
        this->value = value;
    }
    
    ~Variable() = default;

    std::string GetType() const { return type; };

    std::string GetIdentifier() const { return identifier; }
    
    std::any GetValue() const { return value; }

    void SetValue(std::any value) { this->value = value; }

private:
    std::string type;
    std::string identifier;
    std::any value;
};