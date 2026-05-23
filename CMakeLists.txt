cmake_minimum_required(VERSION 3.11)

set(CMAKE_POLICY_DEFAULT_CMP0146 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0148 NEW)

project(kau C CXX)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin
)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

set(
    OPENCV_BUILD_LIST
    "core, imgproc, videoio"
)

set(
    BUILD_LIST ${OPENCV_BUILD_LIST}
    CACHE STRING "" FORCE
)

set(
    BUILD_SHARED_LIBS OFF
    CACHE BOOL "" FORCE
)

set(
    BUILD_TESTS OFF
    CACHE BOOL "" FORCE
)

set(
    BUILD_PERF_TESTS OFF
    CACHE BOOL "" FORCE
)

set(
    BUILD_EXAMPLES OFF
    CACHE BOOL "" FORCE
)

set(
    WITH_WEBP OFF
    CACHE BOOL "" FORCE
)

set(
    WITH_JPEG OFF
    CACHE BOOL "" FORCE
)

set(
    WITH_TIFF OFF
    CACHE BOOL "" FORCE
)

set(
    WITH_OPENEXR OFF
    CACHE BOOL "" FORCE
)

set(
    CPU_BASELINE NONE
    CACHE STRING "" FORCE
)

set(
    CPU_DISPATCH ""
    CACHE STRING "" FORCE
)

set(
    ENABLE_SSE OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_SSE2 OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_SSE3 OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_SSSE3 OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_SSE41 OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_SSE42 OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_AVX OFF
    CACHE BOOL "" FORCE
)

set(
    ENABLE_AVX2 OFF
    CACHE BOOL "" FORCE
)

set(
    WITH_IPP OFF
    CACHE BOOL "" FORCE
)

FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.13.0
)

FetchContent_MakeAvailable(opencv)

FetchContent_Declare(
    glaze
    GIT_REPOSITORY https://github.com/stephenberry/glaze.git
    GIT_TAG v7.7.0
)

FetchContent_MakeAvailable(glaze)

add_executable(
    ${PROJECT_NAME}
    src/main.c
    src/stage/info.cpp
    src/layout/lane.c
    src/layout/info.c
    src/layout/video.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${opencv_SOURCE_DIR}/modules/core/include
    ${opencv_SOURCE_DIR}/modules/imgproc/include
    ${opencv_SOURCE_DIR}/modules/videoio/include
    ${opencv_SOURCE_DIR}/modules/imgcodecs/include
    ${opencv_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    raylib
    opencv_core
    opencv_imgproc
    opencv_videoio
    glaze::glaze
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
