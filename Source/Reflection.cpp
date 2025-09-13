#include "Reflection.hpp"

#include "Components/Transform.hpp"
#include "entt/meta/factory.hpp"
#include "glm/fwd.hpp"

namespace Emerald
{
    void Reflection::initialize()
    {
        using namespace entt::literals;

        entt::meta_factory<Transform>{}
        .type("Transform"_hs)
        .ctor<>()
        .ctor<const glm::vec3&, const glm::quat&, const glm::vec3&>();
    }

    void Reflection::destroy()
    {
        entt::meta_reset();
    }
} // namespace Emerald
