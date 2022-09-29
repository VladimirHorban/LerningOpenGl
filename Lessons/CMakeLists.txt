cmake_minimum_required(VERSION 3.8+)

project(Lessons)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDES ${PROJECT_SOURCE_DIR}*.cpp)

add_library(Lessons SHARED ${SOURCES} ${INCLUDES})

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

target_include_directories(Lessons PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/Core)
target_link_libraries(Lessons ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw glm::glm Core)