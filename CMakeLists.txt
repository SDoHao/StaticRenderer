cmake_minimum_required(VERSION 3.15)
project(RenderProiject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ====================== GLM 纯头文件库：仅下载源码，不构建（修复CMP0169警告） ======================
set(glm_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/glm")
if(NOT EXISTS ${glm_SOURCE_DIR})
    message(STATUS "Clone glm into ${glm_SOURCE_DIR}")
    FetchContent_Populate(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        1.0.3
        GIT_SHALLOW    ON
        GIT_PROGRESS   ON
        SOURCE_DIR     ${glm_SOURCE_DIR}
    )
endif()

# ====================== minifb 需要编译：下载 + add_subdirectory ======================
FetchContent_Declare(
    minifb
    GIT_REPOSITORY https://github.com/emoon/minifb.git
    GIT_TAG        v0.10.1
    GIT_SHALLOW    ON
    GIT_PROGRESS   ON
)
FetchContent_MakeAvailable(minifb)

# 项目源码收集
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/source/*.h"
    "${CMAKE_SOURCE_DIR}/source/*.hpp"
)

add_executable(render ${APP_SOURCES} main.cpp)

# 头文件路径
target_include_directories(render PRIVATE
    "${CMAKE_SOURCE_DIR}/source"
    ${glm_SOURCE_DIR}
)

# 链接编译库
target_link_libraries(render PRIVATE
    minifb
)

# Windows系统库
if(WIN32)
    target_link_libraries(render PRIVATE
        opengl32
        gdi32
        winmm
        user32
        kernel32
        winspool
        shell32
        oleaut32
        uuid
        comdlg32
        advapi32
    )
endif()