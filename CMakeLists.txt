cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

set(PROJECT_NAME "OpenGLZero")
set(SDL2_DIR "external/SDL2-2.0.9")
set(GLEW_SOURCE_DIR "external/glew-2.1.0")
set(GLM_SOURCE_DIR "external/glm-0.9.9.3")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
find_package(OpenGL REQUIRED)
add_subdirectory(${SDL2_DIR})
include_directories(${GLEW_SOURCE_DIR}/include
					${GLM_SOURCE_DIR}
					${SDL2_DIR}/include)
# building glew as a static library
add_library(glew STATIC
	${GLEW_SOURCE_DIR}/src/glew.c
	${GLEW_SOURCE_DIR}/include)
add_definitions(-DGLEW_STATIC)

set(OPENGLZERO_SOURCE ${OPENGLZERO_SOURCE}
    src/Camera.cpp
    src/Camera.h
    src/main.cpp
    src/Platform.h
    src/Renderer.cpp
    src/Renderer.h
    src/Scene.cpp
    src/Scene.h
)
add_executable(${PROJECT_NAME} ${OPENGLZERO_SOURCE})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static ${OPENGL_LIBRARY} glew)