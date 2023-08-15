#pragma once

#include <string>
#include <string_view>

namespace guiBase {
    enum class LogLevel {
        none = 0,
        critical,
        error,
        warning,
        info,
        trace,
    };

    std::string LogLevelStr(LogLevel level);

    class Logger {
    public:
        Logger() = default;
        virtual ~Logger() = default;
        Logger(const Logger& other) = delete;
        Logger(Logger&&) noexcept = delete;

    public:
        Logger& operator=(const Logger&) = delete;
        bool operator==(const Logger& other) const = delete;
        Logger& operator=(Logger&&) noexcept = delete;

    public:
        static void critical(const std::string_view str);
        static void error(const std::string_view str);
        static void warning(const std::string_view str);
        static void info(const std::string_view str);
        static void trace(const std::string_view str);
        static void setLogLevel(const LogLevel& level);

    private:
        static void print(const std::string_view text,
                          const std::string_view colorStart = "\033[0m",
                          const std::string_view colorReset = "\033[0m");

    private:
        static LogLevel logLevel;
    };

}// namespace guiBase

template<typename T>
concept stringType = std::same_as<T, std::string_view> || std::same_as<T, std::string> || std::same_as<T, const char*>;

template<stringType T> constexpr auto LOG_CRITICAL(T str) {
    return guiBase::Logger::critical(str);
}

template<stringType T> constexpr auto LOG_ERROR(T str) {
    return guiBase::Logger::error(str);
}

template<stringType T> constexpr auto LOG_WARNING(T str) {
    return guiBase::Logger::warning(str);
}

template<stringType T> constexpr auto LOG_INFO(T str) {
    return guiBase::Logger::info(str);
}

template<stringType T> constexpr auto LOG_TRACE(T str) {
    return guiBase::Logger::trace(str);
}
