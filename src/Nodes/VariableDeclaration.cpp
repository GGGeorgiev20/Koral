#include "VariableDeclaration.hpp"

VariableDeclaration::VariableDeclaration(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == 3);

    this->type = std::any_cast<std::string>(attributes[0]);
    this->identifier = std::any_cast<std::string>(attributes[1]);

    this->expression = nullptr;
    if (attributes[2].type() == typeid(std::shared_ptr<Node>))
        this->expression = std::any_cast<std::shared_ptr<Node>>(attributes[2]);
}

void VariableDeclaration::Execute()
{
    if (expression == nullptr)
        ExecuteNull();
    else if (expression->GetType() == "Literal")
        ExecuteLiteral();
    else if (expression->GetType() == "BinaryExpression")
        ExecuteBinaryExpression();
}

void VariableDeclaration::ExecuteNull()
{
    VariableManager::GetInstance()->AddVariable(type, identifier);
}

void VariableDeclaration::ExecuteLiteral()
{
    auto value = expression->GetAttributes()[0];
    VariableManager::GetInstance()->AddVariable(type, identifier, value);
}

void VariableDeclaration::ExecuteBinaryExpression()
{
    std::cout << "ExecuteBinaryExpression" << std::endl;
}

std::vector<std::any> VariableDeclaration::GetAttributes()
{
    return { type, identifier, expression };
}