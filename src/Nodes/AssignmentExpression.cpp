#include "AssignmentExpression.hpp"

AssignmentExpression::AssignmentExpression(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == attributesCount);

    this->variable = std::any_cast<std::shared_ptr<Node>>(attributes[0]);
    this->expression = std::any_cast<std::shared_ptr<Node>>(attributes[1]);
}

void AssignmentExpression::Execute()
{
    std::cout << "AssignmentExpression::Execute()" << std::endl;
}

std::vector<std::any> AssignmentExpression::GetAttributes()
{
    return { variable, expression };
}