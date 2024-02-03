#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "Errors.hpp"

#include "../Util/ArgumentManager.hpp"

class ErrorManager
{
public:
    ErrorManager() {};

    static std::shared_ptr<ErrorManager> GetInstance()
    {
        if (instance == nullptr)
            instance = std::make_shared<ErrorManager>();

        return instance;
    }

    void FileError(std::string message);

    void SyntaxError(std::string message, size_t line);

    void RuntimeError(std::string message, size_t line = -1);

    void PrintRed(std::string message);

private:
    static std::shared_ptr<ErrorManager> instance;
};