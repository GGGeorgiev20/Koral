#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "ErrorManager.hpp"

class FileReader
{
public:
    FileReader(const std::string& filename) : filename(filename) {};

    std::string Read();

private:
    std::string filename;
};