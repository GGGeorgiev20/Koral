#include "Literal.hpp"

Literal::Literal(const std::vector<std::any>& attributes)
{
    assert(attributes.size() == attributesCount);

    value = attributes[0];
}

void Literal::Execute()
{
    std::cout << "Literal::Execute()" << std::endl;
}

std::vector<std::any> Literal::GetAttributes()
{
    return { value };
}