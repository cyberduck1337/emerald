cmake_minimum_required(VERSION 3.11)
project(Emerald)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 11.2.0)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_Declare(glm GIT_REPOSITORY	https://github.com/g-truc/glm.git GIT_TAG 1.0.1)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

add_executable(Emerald
    main.cpp
)

target_link_libraries(Emerald PUBLIC
    fmt
    glfw
    glm
)
