cmake_minimum_required(VERSION 3.21)
project(guiBase)

find_package(Vulkan REQUIRED) # must be before vender include to prevent the broken GLFW custom include
find_package(Threads REQUIRED)

set(vendorPath "${PROJECT_SOURCE_DIR}/vendor")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(buildGuiBaseExample "should the example be build?" false)
option(buildGuiBaseMultiThreaded "should the lib be build multithreaded?" true)

add_subdirectory(vendor)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        # prevent C++98 compatability/errors
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        # prevent c-style cast warnings
        -Wno-old-style-cast
        # prevent warning noting unknown documentation warnings
        -Wno-documentation-unknown-command
        -Wno-documentation-deprecated-sync
        -Wno-documentation
        -Wno-global-constructors
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # for GCC and Clang
    add_compile_options(-Wall -Werror -Wextra -Wconversion -Wunused)
    if(buildGuiBaseMultiThreaded)
        #TODO fix multithreaded build
        #include(ProcessorCount)
        #ProcessorCount(CPU_CORE_COUNT)
        #add_compile_options("-j ${CPU_CORE_COUNT}")
    endif()
elseif(MSVC)
    # for MSVC
    add_compile_options(/W4 /WX)
    # /W4 == warning level 4 (equivilant to Wall)
    # /WX == treating warnings as errors
    if(buildGuiBaseMultiThreaded)
        add_compile_options(/MP)
    endif()
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

if(buildGuiBaseExample)
add_subdirectory(example)
endif()

#TODO make tests
#add_subdirectory(tests)
