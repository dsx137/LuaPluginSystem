cmake_minimum_required(VERSION 3.0)

project(LUA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(${PROJECT_SOURCE_DIR}/src lua_srcs)

add_library(${PROJECT_NAME} STATIC ${lua_srcs})