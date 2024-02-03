#pragma once

#include "Interpreter.hpp"

#include "Util/FileReader.hpp"
#include "Util/ArgumentManager.hpp"

class Compiler
{
public:
    Compiler(int argc, char* argv[]);

    void ReadFile();

    void LexContent();

    void ParseTokens();

    void InterpretTree();

    void Compile();

private:
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Node>> AST;

    std::string filename;
    std::string content;

    bool inDevMode = true;
};