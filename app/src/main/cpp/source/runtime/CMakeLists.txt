set(TARGET_NAME GameRuntime)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

#MESSAGE("header files: ${HEADER_FILES}")
#MESSAGE("source files: ${SOURCE_FILES}")
# -- add source files --
source_group(
    TREE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES
    ${HEADER_FILES}
    ${SOURCE_FILES}
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
# -- create library --
add_library(
    ${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
    CXX_STANDARD 17
)
# link dependencies
target_link_libraries(
    ${TARGET_NAME}
    PUBLIC
    imgui
)
target_link_libraries(
    ${TARGET_NAME}
    PUBLIC
    glm
)
target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    stb
)
target_link_libraries(
    ${TARGET_NAME}
    PUBLIC
    spdlog
)
target_link_libraries(
    ${TARGET_NAME}
    PUBLIC
    json11
)

