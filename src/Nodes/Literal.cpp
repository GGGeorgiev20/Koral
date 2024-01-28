#include "Literal.hpp"

Literal::Literal(std::vector<std::any> attributes)
{
    assert(attributes.size() == attributesCount);

    value = attributes[0];
    type = std::any_cast<std::string>(attributes[1]);
}

void Literal::Execute()
{
    std::cout << "Literal::Execute()" << std::endl;
}

std::vector<std::any> Literal::GetAttributes()
{
    return { value, type };
}