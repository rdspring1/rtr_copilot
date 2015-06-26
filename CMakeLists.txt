cmake_minimum_required (VERSION 2.8)
project (rtr_copilot)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set (CMAKE_C_FLAGS			"-std=c99 -pedantic -g -O0")

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories (${CMAKE_SOURCE_DIR})

file(GLOB LINEAR_PENDULUM_AUTOGEN_SRC_FILES "linear_pendulum_autogen/*.c")
file(GLOB PROJECT_SRC_FILES "src/*.c")
add_executable(rtr_copilot ${LINEAR_PENDULUM_AUTOGEN_SRC_FILES} ${PROJECT_SRC_FILES} rt_reachability.c)
add_executable(vector_field ${LINEAR_PENDULUM_AUTOGEN_SRC_FILES} ${PROJECT_SRC_FILES} vector_field.c)

target_include_directories(rtr_copilot PUBLIC "${PROJECT_SOURCE_DIR}/linear_pendulum_autogen/include")
target_include_directories(vector_field PUBLIC "${PROJECT_SOURCE_DIR}/linear_pendulum_autogen/include")
