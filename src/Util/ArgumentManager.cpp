#include "ArgumentManager.hpp"

std::shared_ptr<ArgumentManager> ArgumentManager::instance = nullptr;

void ArgumentManager::SetArgs(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

void ArgumentManager::CheckArgs()
{
    if (argc < 2)
    {
        ErrorManager::GetInstance()->FileError(FILE_NOT_SPECIFIED);
    }
    
    this->filename = argv[1];

    size_t dotPosition = filename.find_last_of('.');
    std::string extension = filename.substr(dotPosition + 1);

    if (extension != "kor" || dotPosition == std::string::npos)
    {
        ErrorManager::GetInstance()->FileError(FILE_INVALID_EXTENSION);
    }

    if (argc >= 3)
    {
        this->devMode = strcmp(argv[2], "dev") == 0;
    }
}

std::string ArgumentManager::GetFilename()
{
    // NOTE: File name can be null, so always check if it's parsed from the arguments.
    //       Dev mode is false by default, so don't bother checking
    if (filename.empty())
    {
        CheckArgs();
    }
    
    return filename;
}

bool ArgumentManager::GetDevMode()
{
    return devMode;
}