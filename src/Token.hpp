#pragma once

#include <iostream>
#include <string>

class Token
{
public:
    Token(std::string& value, size_t& line);

    void SetType(std::string& type) { this->type = type; }
    void SetValue(std::string& value) { this->value = value; }

    std::string GetType() { return type; }
    std::string GetValue() { return value; }
    size_t GetLine() { return line; };

private:
    std::string type;
    std::string value;
    size_t line;
};