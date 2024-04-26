cmake_minimum_required(VERSION 3.20)
project(FormelSamling) # Omdøb senere

# Find ImGui from vendor
add_subdirectory(vendor/imgui)

# Check if SDL2 is installed
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    message(STATUS "SDL2 was not found. Downloading and building from source...")
    include(FetchContent)
    FetchContent_Declare(SDL2 URL https://github.com/libsdl-org/SDL/releases/tag/release-2.30.2)
    
    FetchContent_GetProperties(SDL2)

    if(NOT SDL2_POPULATED)
        FetchContent_Populate(SDL2)
        add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)