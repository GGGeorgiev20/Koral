#include "BinaryExpression.hpp"

BinaryExpression::BinaryExpression(std::vector<std::any> attributes)
{
    assert(attributes.size() == attributesCount);

    this->left = std::any_cast<std::shared_ptr<Node>>(attributes[0]);
    this->right = std::any_cast<std::shared_ptr<Node>>(attributes[1]);
    this->op = std::any_cast<std::string>(attributes[2]);
}

void BinaryExpression::Execute()
{
    std::cout << "BinaryExpression::Execute()" << std::endl;
}

std::vector<std::any> BinaryExpression::GetAttributes()
{
    return { left, right, op };
}