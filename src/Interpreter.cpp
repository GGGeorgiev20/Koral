#include "Interpreter.hpp"

void Interpreter::ExecuteNodes()
{
    for (auto& node : AST)
    {
        printf("%s\n", node->GetType().c_str());
    }
}