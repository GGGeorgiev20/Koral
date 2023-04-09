#include "VariableDeclaration.hpp"

VariableDeclaration::VariableDeclaration(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == attributesCount);

    this->type = std::any_cast<std::string>(attributes[0]);
    this->identifier = std::any_cast<std::string>(attributes[1]);
}

void VariableDeclaration::Execute()
{
    printf("Declaring variable '%s' of type '%s'\n", identifier.c_str(), type.c_str());
}

std::vector<std::any> VariableDeclaration::GetAttributes()
{
    return { type, identifier };
}