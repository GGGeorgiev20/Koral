#include "ExpressionStatement.hpp"

ExpressionStatement::ExpressionStatement(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == attributesCount);

    this->identifier = std::any_cast<std::string>(attributes[0]);
    this->expression = std::any_cast<std::shared_ptr<Node>>(attributes[1]);
}

void ExpressionStatement::Execute()
{
    printf("Updating value of variable '%s'\n", identifier.c_str());
}

std::vector<std::any> ExpressionStatement::GetAttributes()
{
    return { identifier, expression };
}