#include "Compiler.hpp"

Compiler::Compiler(int argc, char* argv[])
{
    auto argumentManager = ArgumentManager::GetInstance();

    argumentManager->SetArgs(argc, argv);

    this->filename = argumentManager->GetFilename();
}

void Compiler::ReadFile()
{
    auto reader = std::make_shared<FileReader>(filename);

    std::string content = reader->Read();

    this->content = content;
}

void Compiler::LexContent()
{
    auto lexer = std::make_shared<Lexer>(content);

    auto tokens = lexer->Lex();

    this->tokens = tokens;
}

void Compiler::ParseTokens()
{
    auto parser = std::make_shared<Parser>(tokens);

    auto tree = parser->Parse();

    this->AST = tree;
}

void Compiler::InterpretTree()
{
    auto interpreter = std::make_shared<Interpreter>(AST);

    interpreter->ExecuteNodes();
}

void Compiler::Compile()
{
    this->ReadFile();

    this->LexContent();

    for (auto token : tokens)
    {
        printf("%s - %s (%lld)\n", token->GetValue().c_str(), token->GetType().c_str(), token->GetLine() + 1);
    }

    this->ParseTokens();

    this->InterpretTree();
}