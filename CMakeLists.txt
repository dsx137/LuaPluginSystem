cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

project(plugsome)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LUA_DIR "./lib/lua-5.4.6")

aux_source_directory(${PROJECT_SOURCE_DIR}/src srcs)

add_subdirectory(${LUA_DIR} LUA)
add_executable(${PROJECT_NAME}
    ${srcs}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    LUA
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${LUA_DIR}/src
)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)