cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

project(plugsome)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LUA_DIR "./lib/lua-5.4.6")
set(SOL_DIR "./lib/sol2")

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
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
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOL_DIR}/include
)

if(CMAKE_BUILD_TYPE MATCHES Release OR CMAKE_BUILD_TYPE MATCHES MinSizeRel)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
endif()