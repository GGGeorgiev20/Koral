#pragma once

#include <iostream>
#include <string>
#include <map>

#include "../Util/ArgumentManager.hpp"

enum class LogType
{
    Debug,
    Info,
    Notice,
    Warning,
    Error,
    Fatal
};

namespace LogManager
{
    // TODO: Implement message formatting for logs

    // NOTE: This is only used when in dev mode

    void Log(LogType type, std::string message);

    void Assert(std::string message, bool condition);
}