cmake_minimum_required(VERSION 3.5)

# set the default build tp debug
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# get folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# define cmake variables for file location
file (GLOB USER_FILES
"src/*.h"
"src/*.cpp"
"src/classifiers/*.h"
"src/classifiers/*.cpp"
)

add_executable(main "app/main.cpp" ${USER_FILES})

target_include_directories(main PUBLIC "src")