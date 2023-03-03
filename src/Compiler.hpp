#pragma once

#include "Interpreter.hpp"
#include "./Util/FileReader.hpp"

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
    std::shared_ptr<FileReader> reader;
    std::shared_ptr<ErrorManager> errorManager;

    std::shared_ptr<Lexer> lexer;
    std::shared_ptr<Parser> parser;
    std::shared_ptr<Interpreter> interpreter;

    std::string filename;
    std::string content;

    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Node>> AST;
};