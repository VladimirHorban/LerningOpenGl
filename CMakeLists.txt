cmake_minimum_required(VERSION 3.8)

project(Lerning_OpenGl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Add Core lib
add_subdirectory(Core)
list(APPEND EXTRA_LIBS Core)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Core")

# Add Lessons lib
add_subdirectory(Lessons)
list(APPEND EXTRA_LIBS Lessons)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Lessons")

add_executable(Lerning_OpenGl main.cpp)

target_link_libraries(Lerning_OpenGl PUBLIC ${EXTRA_LIBS})
target_include_directories(Lerning_OpenGl PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})