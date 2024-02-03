#include "ErrorManager.hpp"

std::shared_ptr<ErrorManager> ErrorManager::instance = nullptr;

void ErrorManager::FileError(std::string message)
{
    printf("koral: fatal error: %s\n", message.c_str());
    printf("compilation terminated.\n");
    exit(1);
}

void ErrorManager::SyntaxError(std::string message, size_t line)
{
    PrintRed("SyntaxError");
    printf(": %s (", message.c_str());
    PrintRed("file");
    printf(": %s, line: ", ArgumentManager::GetInstance()->GetFilename().c_str());
    PrintRed(std::to_string(line + 1));
    printf(")\n");
    exit(1);
}

void ErrorManager::RuntimeError(std::string message, size_t line)
{
    PrintRed("RuntimeError");
    printf(": %s (", message.c_str());
    PrintRed("file");
    printf(": %s, line: ", ArgumentManager::GetInstance()->GetFilename().c_str());
    PrintRed(std::to_string(line + 1));
    printf(")\n");
    exit(1);
}

void ErrorManager::PrintRed(std::string message)
{
    printf("\033[1;31m");
    printf("%s", message.c_str());
    printf("\033[0m");
}