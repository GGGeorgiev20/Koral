#include "Interpreter.hpp"

void Interpreter::ExecuteNodes()
{
    variableManager = VariableManager::GetInstance();

    for (auto& node : AST)
    {
        printf("%s\n", node->GetType().c_str());

        // node->Execute();
    }
}