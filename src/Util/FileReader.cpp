#include "FileReader.hpp"

std::string FileReader::Read()
{
    std::ifstream file(this->filename);

    if (!file.is_open())
        ErrorManager::GetInstance()->FileError(FILE_NOT_FOUND);

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    return content;
}