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
    ImGui
)

target_include_directories(
    guiBase
    PUBLIC
    "src/"
    "${vendorPath}/imgui"
    "${vendorPath}/glfw/include"
    "${Vulkan_INCLUDE_DIRS}"
)
