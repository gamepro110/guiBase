# example config

file(
    GLOB_RECURSE
    exampleSrc
    "src/*.h"
    "src/*.cpp"
)

add_executable(
    example_app
    EXCLUDE_FROM_ALL
    "${exampleSrc}"
)

target_link_libraries(
    example_app
    PUBLIC
    guiBase
)

target_include_directories(
    example_app
    PUBLIC
    "${PROJECT_SOURCE_DIR}/guiBase/src/"
)
