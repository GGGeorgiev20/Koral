#include "AssignmentExpression.hpp"

AssignmentExpression::AssignmentExpression(std::vector<std::any> attributes)
{
    assert(attributes.size() == attributesCount);

    this->variable = std::any_cast<std::shared_ptr<Node>>(attributes[0]);
}

void AssignmentExpression::Execute()
{
    std::cout << "AssignmentExpression::Execute()" << std::endl;
}

std::vector<std::any> AssignmentExpression::GetAttributes()
{
    return { variable };
}