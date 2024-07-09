cmake_minimum_required(VERSION 3.27)
project(2324L_22_s30765_SR)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(2324L_22_s30765_SR
        main.cpp
        image_utils.cpp
        image_utils.h
        steganography.cpp
        steganography.h
        utils.cpp
        utils.h
)
target_link_libraries(2324L_22_s30765_SR
        fmt::fmt
        sfml-graphics
        sfml-window
        sfml-system
)


