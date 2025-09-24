#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "Gfx.hpp"

namespace Emerald
{
    enum class AssetId : uint32_t
    {
        ASSET_INDEX_FIRST,

        TEXTURES_BEGIN = ASSET_INDEX_FIRST,
        TEXTURE_0 = TEXTURES_BEGIN,
        TEXTURES_END,

        ASSET_INDEX_LAST,
    };

    class AssetManager final
    {
        static constexpr size_t MAX_ASSETS = static_cast<size_t>(AssetId::ASSET_INDEX_LAST);

    public:
        AssetManager() = delete;
        ~AssetManager() = delete;

        static void initialize();
        static void destroy();

        template<typename T, AssetId ID>
        static T get()
        {
            static_assert(std::is_same_v<T, Gfx::Texture2d> && (ID >= AssetId::TEXTURES_BEGIN && ID <= AssetId::TEXTURES_END));   
        }

    private:
        static inline std::array<void*, MAX_ASSETS> g_assets{}; 
    };
}
