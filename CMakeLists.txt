cmake_minimum_required(VERSION 3.24)
project(guiBase)

find_package(Vulkan REQUIRED) # must be before vender include to prevent the broken GLFW custom include
find_package(Threads REQUIRED)

include(cmake_scripts/CPM.cmake)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(USE_LD "" CACHE STRING "which linker to use")
set_property(CACHE USE_LD PROPERTY STRINGS "" "bfd" "gold" "lld" "mold")

option(buildGuiBaseExample "should the guiBase example be build?" false)

add_subdirectory(vendor)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # for GCC and Clang
    add_compile_options(-Wall -Werror -Wextra -Wunused)

    if (USE_LD)
        add_link_options(-fuse-ld=${USE_LD}) # set use of specified linker
    endif()
elseif(MSVC)
    # for MSVC
    add_compile_options(/W4 /WX /permissive-)
    # /W4 == warning level 4 (equivilant to Wall)
    # /WX == treating warnings as errors
else()
    message(WARNING "Unsupported compiler detected, flags wont be set correctly")
endif()

set(currentPreset ${CMAKE_BUILD_TYPE})
if(currentPreset STREQUAL "Debug")
	add_definitions(-DDEBUG)
elseif(currentPreset STREQUAL "Release")
	add_definitions(-DRELEASE)
elseif(currentPreset STREQUAL "MinSizeRel")
	add_definitions(-DDIST)
endif()

add_subdirectory(guiBaseLib)

if(PROJECT_IS_TOP_LEVEL)
    set(buildGuiBaseExample true)
endif(PROJECT_IS_TOP_LEVEL)

if(buildGuiBaseExample)
add_subdirectory(example)
endif()

#TODO make tests
#add_subdirectory(tests)
