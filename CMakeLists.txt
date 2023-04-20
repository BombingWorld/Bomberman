## RAYLIB CMAKE PART

cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

project(bomberman)

# Generate compile_commands.json
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.17)
set(${CMAKE_BINARY_DIR} build/)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_BUILD_TYPE Release)

# Dependencies
find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED

if (NOT raylib_FOUND)
  INCLUDE(FetchContent)

  FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz)
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    SET(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    SET(raylib_FOUND TRUE)
  endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


## INDIE CMAKE PART

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# add the executable
add_executable(bomberman main.cpp ProjectManager.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} raylib)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/bomberman
        DESTINATION bin
        RENAME ${CMAKE_PROJECT_NAME}-bomberman)