#include "CallExpression.hpp"

CallExpression::CallExpression(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == 2);

    this->identifier = std::any_cast<std::string>(attributes[0]);
    this->arguments = std::any_cast<std::vector<std::shared_ptr<Node>>>(attributes[1]);
}

void CallExpression::Execute()
{
    // printf("Calling function '%s' with %lld arguments\n", identifier.c_str(), arguments.size());
}

std::vector<std::any> CallExpression::GetAttributes()
{
    return { identifier, arguments };
}