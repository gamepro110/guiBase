# vendor config

## GLFW
CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.4
)
### disable glfw documentation, examples and tests
set(GLFW_BUILD_DOCKS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")

option(buildGuiBaseWayland "should guiBase be build with wayland instead of x11?" true)
if (buildGuiBaseWayland)
# enable wayland and disable x11
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "")
set(GLFW_BUILD_X11 OFF CACHE BOOL "")
endif()

# add_subdirectory(glfw)

## imgui
CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    GIT_TAG "v1.91.8-docking"
    DOWNLOAD_ONLY TRUE
)

add_library(imgui STATIC)
target_sources(
    imgui
    PUBLIC
    ${imgui_SOURCE_DIR}/imconfig.h
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imgui_internal.h
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imstb_rectpack.h
    ${imgui_SOURCE_DIR}/imstb_textedit.h
    ${imgui_SOURCE_DIR}/imstb_truetype.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h
)

target_include_directories(
    imgui
    PUBLIC
    ${imgui_SOURCE_DIR}
)

target_link_libraries(
    imgui
    PUBLIC
    ${Vulkan_LIBRARIES}
)

target_link_libraries(
    imgui
    PUBLIC
    ${Vulkan_LIBRARIES}
)

set_target_properties(
    imgui
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
