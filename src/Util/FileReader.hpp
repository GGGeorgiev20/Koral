#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "../Logs/ErrorManager.hpp"

class FileReader
{
public:
    FileReader(std::string filename) : filename(filename) {};

    std::string Read();

private:
    std::string filename;
};