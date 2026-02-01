cmake_minimum_required(VERSION 3.10)
project(Danbooru_Crawler VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/Danbooru_Crawler)

# ===== CURL =====
find_package(CURL REQUIRED)

file(GLOB_RECURSE SRC_FILES
    ${SRC_ROOT}/Danbooru_Crawler.cpp
    ${SRC_ROOT}/danbooru/*.cpp
    ${SRC_ROOT}/download/*.cpp
    ${SRC_ROOT}/menu/*.cpp
    ${SRC_ROOT}/config/*.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

# ===== INCLUDE =====
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${SRC_ROOT}
        ${SRC_ROOT}/danbooru
        ${SRC_ROOT}/download
        ${SRC_ROOT}/menu
        ${SRC_ROOT}/config
        ${SRC_ROOT}/thirdParty
)

# ===== LINK (CHỖ QUAN TRỌNG NHẤT) =====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CURL::libcurl
)
