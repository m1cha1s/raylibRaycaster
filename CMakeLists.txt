cmake_minimum_required(VERSION 3.0)

project(reylibTest)

set(CMAKE_C_STANDARD 11)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

file(GLOB sources ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)