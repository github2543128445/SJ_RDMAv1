project (rlib)

cmake_minimum_required(VERSION 2.8)

## use C++11 features
add_definitions(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

## path to ralloc lib, which you need to build manually
set(RALLOC_LIB "${PROJECT_SOURCE_DIR}/ralloc/libssmalloc.a")

## include paths
include_directories(ralloc)

file(GLOB SOURCES "*.hpp")

add_library(rdma STATIC ${SOURCES})
set_target_properties(rdma PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rdma -lpthread ibverbs ${RALLOC_LIB})

add_executable(server "example/server.cpp")
add_executable(client "example/client.cpp")
add_executable(RC_READ_client "RC_READ/client.cpp")
add_executable(RC_READ_server "RC_READ/server.cpp")

target_link_libraries(server rdma)
target_link_libraries(client rdma)
target_link_libraries(RC_READ_client rdma)
target_link_libraries(RC_READ_server rdma)

