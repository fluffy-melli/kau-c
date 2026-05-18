cmake_minimum_required(VERSION 3.11)

project(kau C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options("/utf-8")

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

set(WITH_IPP OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_tests OFF CACHE BOOL "" FORCE)

set(BUILD_LIST core, imgproc, videoio CACHE STRING "" FORCE)

FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.13.0
)

FetchContent_MakeAvailable(opencv)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${opencv_SOURCE_DIR}/modules/core/include
    ${opencv_SOURCE_DIR}/modules/imgproc/include
    ${opencv_SOURCE_DIR}/modules/videoio/include
    ${opencv_SOURCE_DIR}/modules/imgcodecs/include
    ${opencv_SOURCE_DIR}/include
    ${opencv_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    raylib
    opencv_core
    opencv_imgproc
    opencv_videoio
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
