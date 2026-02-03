cmake_minimum_required(VERSION 3.10)
project(Danbooru_Crawler VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/Danbooru_Crawler)

find_package(CURL REQUIRED)

file(GLOB_RECURSE SRC_FILES
    ${SRC_ROOT}/Danbooru_Crawler.cpp
    ${SRC_ROOT}/danbooru/*.cpp
    ${SRC_ROOT}/download/*.cpp
    ${SRC_ROOT}/menu/*.cpp
    ${SRC_ROOT}/config/*.cpp
    ${SRC_ROOT}/net/*.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${SRC_ROOT}
        ${SRC_ROOT}/danbooru
        ${SRC_ROOT}/download
        ${SRC_ROOT}/menu
        ${SRC_ROOT}/config
        ${SRC_ROOT}/thirdParty
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CURL::libcurl
)
