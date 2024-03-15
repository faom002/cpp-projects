cmake_minimum_required(VERSION 3.27)
project(Pmall)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_VERBOSE_MAKEFILE ON)
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)


FetchContent_Declare(
        RayLib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 4.5.0
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(RayLib)

add_executable(Pmall main.cpp include/Component.h include/Transform.h include/Entity.h include/Layer.h include/Scene.h include/Components/RectangleGizmo.h include/Components/ExampleInput.h RectangleGizmoComponent.cpp ExampleInputComponent.cpp)
target_link_libraries(Pmall PUBLIC raylib)
target_include_directories(Pmall PUBLIC include)
