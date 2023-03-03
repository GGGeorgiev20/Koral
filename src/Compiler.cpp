#include "Compiler.hpp"

Compiler::Compiler(int argc, char* argv[])
{
    errorManager = ErrorManager::GetInstance();

    errorManager->SetArgs(argc, argv);

    this->filename = errorManager->CheckFile();
}

void Compiler::ReadFile()
{
    reader = std::make_shared<FileReader>(filename);

    std::string content = reader->Read();

    this->content = content;
}

void Compiler::LexContent()
{
    lexer = std::make_shared<Lexer>(content);

    auto tokens = lexer->Lex();

    this->tokens = tokens;
}

void Compiler::ParseTokens()
{
    parser = std::make_shared<Parser>(tokens);

    auto tree = parser->Parse();

    this->AST = tree;
}

void Compiler::InterpretTree()
{
    interpreter = std::make_shared<Interpreter>(AST);

    interpreter->ExecuteNodes();
}

void Compiler::Compile()
{
    this->ReadFile();

    this->LexContent();

    this->ParseTokens();

    this->InterpretTree();
}