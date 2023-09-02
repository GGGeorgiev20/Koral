#include "VariableReference.hpp"

VariableReference::VariableReference(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == attributesCount);

    name = std::any_cast<std::string>(attributes[0]);
}

void VariableReference::Execute()
{
    std::cout << "VariableReference::Execute()" << std::endl;
}

std::vector<std::any> VariableReference::GetAttributes()
{
    return { name };
}