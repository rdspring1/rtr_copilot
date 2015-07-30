cmake_minimum_required (VERSION 2.8)
project (rtr_copilot)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set (CMAKE_C_FLAGS			"-std=c99 -pedantic -g -O0")

include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories (${CMAKE_SOURCE_DIR})

file(GLOB PENDULUM_AUTOGEN_SRC_FILES "pendulum_autogen/*.c")
file(GLOB VANDERPOL_AUTOGEN_SRC_FILES "vanderpol_autogen/*.c")
file(GLOB LINEAR_SRC_FILES "linear_system/*.c")
file(GLOB PROJECT_SRC_FILES "src/*.c")

add_executable(rt_reachability ${PENDULUM_AUTOGEN_SRC_FILES} ${LINEAR_SRC_FILES} ${VANDERPOL_AUTOGEN_SRC_FILES} ${PROJECT_SRC_FILES} rt_reachability.c)
target_include_directories(rt_reachability PUBLIC "${PROJECT_SOURCE_DIR}/linear_system/include")
target_include_directories(rt_reachability PUBLIC "${PROJECT_SOURCE_DIR}/pendulum_autogen/include")
target_include_directories(rt_reachability PUBLIC "${PROJECT_SOURCE_DIR}/vanderpol_autogen/include")
target_link_libraries(rt_reachability m)

#add_executable(pendulum_vector_field ${PENDULUM_AUTOGEN_SRC_FILES} ${LINEAR_SRC_FILES} ${PROJECT_SRC_FILES} vector_field.c)
#target_include_directories(pendulum_vector_field PUBLIC "${PROJECT_SOURCE_DIR}/linear_system/include")
#target_include_directories(pendulum_vector_field PUBLIC "${PROJECT_SOURCE_DIR}/pendulum_autogen/include")
#target_link_libraries(pendulum_vector_field m)

#add_executable(vanderpol_vector_field ${VANDERPOL_AUTOGEN_SRC_FILES} ${PROJECT_SRC_FILES} vector_field.c)
#target_include_directories(vanderpol_vector_field PUBLIC "${PROJECT_SOURCE_DIR}/vanderpol_autogen/include")
#target_link_libraries(vanderpol_vector_field m)
