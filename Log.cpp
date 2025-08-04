#include "Log.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"

namespace Emerald
{
    void Log::initialize()
    {
        spdlog::set_level(spdlog::level::trace);
    }

    void Log::destroy()
    {
    }
}
