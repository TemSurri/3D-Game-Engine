cmake_minimum_required(VERSION 3.20)

project(GameEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GLFW configuration
# These must be set before add_subdirectory(GLFW).


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw/glfw-3.4)


# GLAD
# GLAD provides the OpenGL function loader implementation.


add_library(glad STATIC
    external/glad/src/glad.c
 )

target_include_directories(glad PUBLIC
    external/glad/include
)

# main exec files
add_executable(GameEngine
    src/main.cpp

    external/stb/stb_image.cpp
 "src/core/window_manager.h" "src/core/window_manager.cpp" "src/renderer/shader/shader.cpp" "src/renderer/shader/shader.h")

target_include_directories(GameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/stb
)

# Platform-specific OpenGL libraries

if(WIN32)

    target_link_libraries(GameEngine PRIVATE
        glad
        glfw
        opengl32
    )

elseif(APPLE)

    find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)

    target_link_libraries(GameEngine PRIVATE
        glad
        glfw
        ${OPENGL_FRAMEWORK}
    )

elseif(UNIX)

    find_package(OpenGL REQUIRED)

    target_link_libraries(GameEngine PRIVATE
        glad
        glfw
        OpenGL::GL
    )

endif()

# Copy resources beside the executable after every build.
#
# Source:
#   GameEngine/resources/
#
# Destination:
#   build/.../resources/

add_custom_command(
    TARGET GameEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:GameEngine>/resources"

    COMMENT "Copying resources to executable directory"
)

add_custom_command(
    TARGET GameEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/renderer/shader"
        "$<TARGET_FILE_DIR:GameEngine>/renderer/shader"
)