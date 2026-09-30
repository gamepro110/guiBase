# guiBaseLib config

file(
    GLOB_RECURSE
    guiBaseSRC
    "src/*.cpp"
    "src/*.h"
)

add_library(
    guiBase
    STATIC
    "${guiBaseSRC}"
)

set_target_properties(
    guiBase
    PROPERTIES
    VERSION 0.1.0
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(
    guiBase
    PUBLIC
    glfw
    imgui
)

target_include_directories(
    guiBase
    PUBLIC
    "src/"
    "${Vulkan_INCLUDE_DIRS}"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(
        guiBase
        PUBLIC
        -Wno-class-memaccess
    )
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
