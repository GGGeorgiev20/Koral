#include "BinaryExpression.hpp"

BinaryExpression::BinaryExpression(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == 4);

    this->left = std::any_cast<std::shared_ptr<Node>>(attributes[0]);
    this->right = std::any_cast<std::shared_ptr<Node>>(attributes[1]);
    this->op = std::any_cast<Operator>(attributes[2]);

    this->next = std::any_cast<std::shared_ptr<Node>>(attributes[3]);
}

void BinaryExpression::Execute()
{
    std::cout << "BinaryExpression::Execute()" << std::endl;
}

std::vector<std::any> BinaryExpression::GetAttributes()
{
    return { left, right, op, next };
}