#include "Interpreter.hpp"

void Interpreter::ExecuteNodes()
{
    variableManager = VariableManager::GetInstance();

    for (auto& node : AST)
    {
        node->Execute();
    }
}