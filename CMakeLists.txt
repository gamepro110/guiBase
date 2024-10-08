cmake_minimum_required(VERSION 3.22)
project(guiBase)

find_package(Vulkan REQUIRED) # must be before vender include to prevent the broken GLFW custom include
find_package(Threads REQUIRED)

# download CPM.cmake
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

set(vendorPath "${PROJECT_SOURCE_DIR}/vendor")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(USE_LD "" CACHE STRING "which linker to use")
set_property(CACHE USE_LD PROPERTY STRINGS "" "bfd" "gold" "lld" "mold")

option(buildGuiBaseExample "should the guiBase example be build?" false)

if(MSVC)
    option(buildGuiBaseMultiThreaded "should the lib be build multithreaded? (windows specific)" true)
endif(MSVC)

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

    if (USE_LD)
        add_link_options(-fuse-ld=${USE_LD}) # set use of specified linker
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

if(PROJECT_IS_TOP_LEVEL)
    set(buildGuiBaseExample true)
endif(PROJECT_IS_TOP_LEVEL)

if(buildGuiBaseExample)
add_subdirectory(example)
endif()

if(PROJECT_IS_TOP_LEVEL)
    enable_testing()
    add_subdirectory(tests)
endif(PROJECT_IS_TOP_LEVEL)
