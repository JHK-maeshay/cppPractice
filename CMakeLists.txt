cmake_minimum_required(VERSION 3.10)
project(SDtrainDataPreprocessor)
set(CMAKE_CXX_STANDARD 17)
set(ENV{LC_ALL} "C.UTF-8")


# 소스 파일
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/*.cpp")
add_executable(SDtrainDataPreprocessor ${SRC_FILES})


# GLFW 추가
add_subdirectory(source/glfw-master)


# IMGUI 소스 수동 추가
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/source/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)


# 포함 경로
target_include_directories(SDtrainDataPreprocessor PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_SOURCE_DIR}/external/glfw/include
)


# 소스 링크
target_sources(SDtrainDataPreprocessor PRIVATE ${IMGUI_SOURCES})


# 라이브러리 링크
find_package(OpenGL REQUIRED)
target_link_libraries(SDtrainDataPreprocessor
    glfw
    ${OPENGL_gl_LIBRARY}
)