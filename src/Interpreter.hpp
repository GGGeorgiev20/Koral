#pragma once

#include "./Parser.hpp"
// #include "./Variables/VariableManager.hpp"

class Interpreter
{
public:
    Interpreter(std::vector<std::shared_ptr<Node>> AST) : AST(AST) {};

    void ExecuteNodes();

private:
    std::vector<std::shared_ptr<Node>> AST;

    std::shared_ptr<VariableManager> variableManager;
};