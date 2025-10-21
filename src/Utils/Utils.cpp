#include "Utils/Utils.hpp"

#include <fstream>

std::string Utils::ReadFileContent(const std::string& path)
{
    std::ifstream file { path };
    auto fileSize = file.seekg(0, std::ios::end).tellg();
    file.seekg(0);

    std::string fileContent;
    fileContent.resize(fileSize);

    file.read(fileContent.data(), fileSize);

    return fileContent;
}
