#pragma once

#include <iostream>
#include <cstring>
#include <memory>
#include <vector>
#include <string>

#include "../Logs/ErrorManager.hpp"

class ArgumentManager
{
public:
    ArgumentManager() {};

    static std::shared_ptr<ArgumentManager> GetInstance()
    {
        if (instance == nullptr)
            instance = std::make_shared<ArgumentManager>();

        return instance;
    }

    void SetArgs(int argc, char** argv);

    void CheckArgs();

    std::string GetFilename();

    bool GetDevMode();

private:
    static std::shared_ptr<ArgumentManager> instance;

    int argc;
    char** argv;

    std::string filename;
    bool devMode = false;
};