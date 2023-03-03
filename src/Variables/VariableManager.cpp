#include "VariableManager.hpp"

std::shared_ptr<VariableManager> VariableManager::instance = nullptr;

void VariableManager::AddVariable(const std::string& type, const std::string& identifier, std::any value)
{
    auto variable = std::make_shared<Variable>(type, identifier, value);

    variables.push_back(variable);
}

std::shared_ptr<Variable> VariableManager::GetVariableByIdentifier(const std::string& identifier)
{
    for (auto& variable : variables)
    {
        if (variable->GetIdentifier() == identifier)
            return variable;
    }

    return nullptr;
}

std::shared_ptr<Variable> VariableManager::GetVariableByIndex(size_t index)
{
    return variables[index];
}