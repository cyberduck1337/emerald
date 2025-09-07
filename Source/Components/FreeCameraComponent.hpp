#pragma once

namespace Emerald
{
    class FreeCameraComponent
    {
    public:
        FreeCameraComponent(float speed, float sensitivity);

        [[nodiscard]]
        float speed() const;

        [[nodiscard]]
        float sensitivity() const;

    private:
        float m_speed;
        float m_sensitivity;
    };
} // namespace Emerald
