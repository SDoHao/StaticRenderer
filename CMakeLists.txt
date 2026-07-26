cmake_minimum_required(VERSION 3.15)
project(RenderProiject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 管理加入源码参与编译
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
    "${CMAKE_SOURCE_DIR}/source/*.h"
    "${CMAKE_SOURCE_DIR}/source/*.hpp"
)

add_executable(render ${APP_SOURCES} main.cpp)

# 管理include时的文件检索路
target_include_directories(render PRIVATE
    "${CMAKE_SOURCE_DIR}/source"
    "${CMAKE_SOURCE_DIR}/minfb/include"
    "${CMAKE_SOURCE_DIR}/glm"
)

add_subdirectory(minifb)

# 链接minifb，自动继承minifb的头文件、编译参数
target_link_libraries(render PRIVATE minifb)


if(WIN32)
    target_link_libraries(render PRIVATE
        opengl32
        gdi32
        winmm
        user32
        kernel32
        winspool
        shell32
        opengl32
        oleaut32
        uuid
        comdlg32
        advapi32
    )
endif()
