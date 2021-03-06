cmake_minimum_required(VERSION 3.16)
project(raygun CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(add_shader)
include(compile_flags)
include(copy_dlls)
include(source_groups)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMake Build Type" FORCE)
endif()

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING "CMake Configuration Types" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Threads REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory(vendor/assimp)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/imGuIZMO)
add_subdirectory(vendor/json)
add_subdirectory(vendor/OpenAL)
add_subdirectory(vendor/opus)
add_subdirectory(vendor/PhysX)
add_subdirectory(vendor/spdlog)

file(GLOB_RECURSE raygun_srcs raygun/*.cpp raygun/*.hpp)

add_library(raygun STATIC ${raygun_srcs})
target_include_directories(raygun PUBLIC .)
target_link_libraries(raygun PUBLIC
    Threads::Threads
    ${CMAKE_DL_LIBS}

    Vulkan::Vulkan

    assimp
    fmt
    glfw
    glm
    imgui
    imGuIZMO
    json
    opus
    OpenAL
    PhysX
    spdlog
)

target_compile_definitions(raygun PRIVATE RAYGUN_DLL_EXPORT)

target_precompile_headers(raygun PUBLIC raygun/pch.hpp)

file(GLOB_RECURSE shaders
    resources/shaders/*.frag
    resources/shaders/*.vert
    resources/shaders/*.comp
    resources/shaders/*.rgen
    resources/shaders/*.rint
    resources/shaders/*.rahit
    resources/shaders/*.rchit
    resources/shaders/*.rmiss
    resources/shaders/*.rcall
)

file(GLOB_RECURSE shader_dependencies
    resources/shaders/*.h
    resources/shaders/*.def
)

foreach(shader IN LISTS shaders)
    raygun_add_shader(raygun ${shader} "${shader_dependencies}")
endforeach(shader)

raygun_add_compile_flags(raygun)
raygun_enable_warnings(raygun)
raygun_set_source_groups(raygun)
#raygun_copy_dlls($<TARGET_FILE:raygun>)

add_subdirectory(example)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT example)
