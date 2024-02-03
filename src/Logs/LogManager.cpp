#include "LogManager.hpp"

namespace LogManager
{
    std::map<LogType, bool> enabledLogTypes = {
        { LogType::Debug,     true },
        { LogType::Info,      true },
        { LogType::Notice,    true },
        { LogType::Warning,   true },
        { LogType::Error,     true }
    };

    std::map<LogType, std::string> logTypePrefixes = {
        { LogType::Debug,   "DEBUG: " },
        { LogType::Info,    "INFO: " },
        { LogType::Notice,  "NOTICE: " },
        { LogType::Warning, "WARN: " },
        { LogType::Error,   "ERROR: " },
        { LogType::Fatal,   "FATAL: " }
    };

    void Log(LogType type, std::string message)
    {
        if (ArgumentManager::GetInstance()->GetDevMode() == false)
        {
            return;
        }

        auto it = logTypePrefixes.find(type);
        
        if (it == logTypePrefixes.end() || !enabledLogTypes[type])
        {
            return;
        }

        printf("%s%s\n", it->second.c_str(), message.c_str());
    }

    void Assert(std::string message, bool condition)
    {
        if (condition)
        {
            return;
        }

        printf("FATAL: %s\n", message.c_str());
        exit(1);
    }
}