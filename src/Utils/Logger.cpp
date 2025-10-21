#include "Utils/Logger.hpp"

#include <string_view>

#include <fmt/core.h>

std::array<std::string_view, static_cast<size_t>(LogType::Count)> Logger::m_prefixes = {
	"DEBUG", "INFO", "WARN", "ERROR", "FATAL", "ASSERT"
};

std::array<bool, static_cast<size_t>(LogType::Count)> Logger::m_statuses = {
	true, true, true, true, false, false
};

void Logger::Info(std::string_view message)
{
    Log(LogType::Info, message);
}

void Logger::Debug(std::string_view message)
{
    Log(LogType::Debug, message);
}

void Logger::Warning(std::string_view message)
{
    Log(LogType::Warning, message);
}

void Logger::Error(std::string_view message)
{
    Log(LogType::Error, message);
}

void Logger::Fatal(std::string_view message)
{
    Log(LogType::Fatal, message);
    exit(1);
}

void Logger::Assert(bool condition, std::string_view message)
{
    if (condition)
        return;

    Log(LogType::Assert, message);
    exit(1);
}

void Logger::Log(LogType type, std::string_view message)
{
	const int typeIndex = static_cast<int>(type);

	// Fatal and Assert can't be stopped from logging
    if (!m_statuses[typeIndex] && type != LogType::Fatal && type != LogType::Assert)
	    return;

    fmt::println("{}: {}", m_prefixes[typeIndex], message.data());
}
