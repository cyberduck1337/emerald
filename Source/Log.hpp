#pragma once

#include "fmt/base.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <cstdint>

namespace Emerald
{
    class Log final
    {
    public:
        enum class Level : uint32_t
        {
            TRACE = spdlog::level::level_enum::trace,
            DEBUG = spdlog::level::level_enum::debug,
            WARNING = spdlog::level::level_enum::warn,
            ERROR = spdlog::level::level_enum::err,
            INFO = spdlog::level::level_enum::info,
            CRITICAL = spdlog::level::level_enum::critical,
            OFF = spdlog::level::level_enum::off
        };

        Log() = delete;
        ~Log() = delete;

        static void initialize();
        static void destroy();

        template<typename... T>
        static void trace(fmt::format_string<T...> fmt, T&&... args)
        {
            log(Level::TRACE, fmt, std::forward<T>(args)...);
        }
        
        template<typename... T>
        static void debug(fmt::format_string<T...> fmt, T&&... args)
        {
            log(Level::DEBUG, fmt, std::forward<T>(args)...);
        }

        template<typename... T>
        static void info(fmt::format_string<T...> fmt, T&&... args)
        {
            log(Level::INFO, fmt, std::forward<T>(args)...);
        }

        template<typename... T>
        static void warning(fmt::format_string<T...> fmt, T&&... args)
        {
            log(Level::WARNING, fmt, std::forward<T>(args)...);
        }

        template<typename... T>
        static void error(fmt::format_string<T...> fmt, T&&... args)
        {
            log(Level::ERROR, fmt, std::forward<T>(args)...);
        }

        template<typename... T>
        static void critical(fmt::format_string<T...> fmt, T&&... args)
        {
            log(Level::CRITICAL, fmt, std::forward<T>(args)...);
        }

    private:
        template<typename... T>
        static void log(Level level, fmt::format_string<T...> fmt, T&&... args)
        {
            spdlog::log(static_cast<spdlog::level::level_enum>(level), fmt::format(fmt, std::forward<T>(args)...));
        }
    };
}
