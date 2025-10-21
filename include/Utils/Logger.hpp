#pragma once

#include <array>
#include <cstdint>
#include <fmt/core.h>
#include <string_view>

#define nassert(condition, message) \
Logger::Assert(condition, fmt::format("Assert failed on line {} file {} function {}: {}", __LINE__, __FILE__, __FUNCTION__, message))

enum class LogType : uint8_t
{
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
    Assert,
    Count
};

class Logger
{
public:
    static void Info(std::string_view message);

    static void Debug(std::string_view message);

    static void Warning(std::string_view message);

    static void Error(std::string_view message);

    static void Fatal(std::string_view message);

    static void Assert(bool condition, std::string_view message);

private:
	static void Log(LogType type, std::string_view message);

	static std::array<std::string_view, static_cast<size_t>(LogType::Count)> m_prefixes;
	static std::array<bool, static_cast<size_t>(LogType::Count)> m_statuses;
};
