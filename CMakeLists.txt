cmake_minimum_required(VERSION 3.11)
project(Emerald)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(entt GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG v3.15.0)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 11.2.0)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG v0.1.36)
FetchContent_Declare(glm GIT_REPOSITORY	https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.15.3)

FetchContent_MakeAvailable(entt)
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glad)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(spdlog)

add_executable(Emerald
    Assertion.hpp
    Input.hpp
    Input.cpp
    Gfx.hpp
    Gfx.cpp
    Log.hpp
    Log.cpp
    main.cpp
    System.hpp
)

target_link_libraries(Emerald PUBLIC
    fmt
    glad
    glfw
    glm
    spdlog::spdlog
    EnTT::EnTT
)

target_compile_definitions(Emerald PUBLIC
    GLM_ENABLE_EXPERIMENTAL
)
