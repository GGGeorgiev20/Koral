#pragma once

#include "Variable.hpp"

class VariableManager
{
public:
    VariableManager() {}

    static std::shared_ptr<VariableManager> GetInstance()
    {
        if (instance == nullptr)
            instance = std::make_shared<VariableManager>();

        return instance;
    }

    void AddVariable(const std::string& type, const std::string& identifier, std::any value = nullptr);

    std::shared_ptr<Variable> GetVariableByIdentifier(const std::string& identifier);

    std::shared_ptr<Variable> GetVariableByIndex(size_t index);

private:
    static std::shared_ptr<VariableManager> instance;

    std::vector<std::shared_ptr<Variable>> variables;
};