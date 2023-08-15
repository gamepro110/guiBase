# vendor config

## GLFW
### disable glfw documentation, examples and tests
set(GLFW_BUILD_DOCKS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")

# enable wayland and disable x11
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "")
set(GLFW_BUILD_X11 OFF CACHE BOOL "")

add_subdirectory(glfw)

## imgui
file(
    GLOB
    ImGui_src
	"imgui/*.cpp"
	"imgui/*.h"
	"imgui/backends/imgui_impl_glfw.cpp"
	"imgui/backends/imgui_impl_glfw.h"
    "imgui/backends/imgui_impl_vulkan.cpp"
    "imgui/backends/imgui_impl_vulkan.h"
)

add_library(
    ImGui
    STATIC
    "${ImGui_src}"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        ImGui
        PUBLIC
        -Wno-error=conversion
    )
endif()

target_link_libraries(
    ImGui
    PUBLIC
    "${Vulkan_LIBRARIES}"
)

target_include_directories(
    ImGui
    PUBLIC
    "${vendorPath}/imgui"
    "${vendorPath}/glfw/include"
    "${Vulkan_INCLUDE_DIRS}"
)

set_target_properties(
    ImGui
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
