cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(mc VERSION 0.1.0 LANGUAGES C CXX)
set(CXX_MAKE_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw-3.3.8)
add_subdirectory(lib/glad)
add_subdirectory(lib/stb_image)
add_subdirectory(lib/glm)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")

add_executable(mc "${SOURCE_FILES}")

target_include_directories(mc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad stb_image glm)