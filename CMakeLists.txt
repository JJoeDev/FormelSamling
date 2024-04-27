cmake_minimum_required(VERSION 3.20)
project(FormelSamling) # Omdøb senere

# Exports executable to the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# Set minimum required OpenGL version
set(OpenGL_GL_PREFERENCE "GLVND")

# Set the directory of the imgui files we use
set(IMGUI_DIR "${CMAKE_BINARY_DIR}/vendor/imgui")

# Include ImGui
file(GLOB IMGUI_SRC
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/*.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
)

# Find GLFW
find_package(glfw3 REQUIRED)

# Find OpenGL
find_package(OpenGL 3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC} ${IMGUI_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${OPENGL_LIBRARIES})

# Platform specific settings
if(WIN32)
    # Windows settings
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(UNIX AND NOT APPLE)
    # Linux settings
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
elseif(APPLE)
    # Apple settings
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework CoreVideo")
endif()