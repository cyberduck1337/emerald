add_library(EmeraldFramework STATIC
    Assertion.hpp
    Game.hpp
    Game.cpp
    Input.hpp
    Input.cpp
    Gfx.hpp
    Gfx.cpp
    Log.hpp
    Log.cpp
    System.hpp
)

target_include_directories(EmeraldFramework PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(EmeraldFramework PUBLIC
    fmt
    glad
    glfw
    glm
    spdlog::spdlog
    EnTT::EnTT
)

target_compile_definitions(EmeraldFramework PUBLIC
    GLM_ENABLE_EXPERIMENTAL
)
