#include "ErrorManager.hpp"

std::shared_ptr<ErrorManager> ErrorManager::instance = nullptr;

void ErrorManager::SetArgs(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

std::string ErrorManager::CheckFile()
{
    if (argc < 2)
        FileError("no file specified");
    
    if (argc > 2)
        FileError("too many arguments");
    
    this->filename = argv[1];

    size_t dotPosition = filename.find_last_of('.');
    std::string extension = filename.substr(dotPosition + 1);

    if (extension != "kor" || dotPosition == std::string::npos)
        FileError("invalid file extension");

    return filename;
}

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
    printf(": %s, line: ", filename.c_str());
    PrintRed(std::to_string(line + 1));
    printf(")\n");
    exit(1);
}

void ErrorManager::RuntimeError(std::string message, size_t line)
{
    PrintRed("RuntimeError");
    printf(": %s (", message.c_str());
    PrintRed("file");
    printf(": %s, line: ", filename.c_str());
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