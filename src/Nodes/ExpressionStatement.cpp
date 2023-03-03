#include "ExpressionStatement.hpp"

ExpressionStatement::ExpressionStatement(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == 2);

    this->identifier = std::any_cast<std::string>(attributes[0]);
    this->expression = std::any_cast<std::shared_ptr<Node>>(attributes[1]);
}

void ExpressionStatement::Execute()
{
    std::cout << "ExpressionStatement::Execute()" << std::endl;
}

std::vector<std::any> ExpressionStatement::GetAttributes()
{
    return { identifier, expression };
}