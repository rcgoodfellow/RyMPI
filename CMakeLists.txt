cmake_minimum_required(VERSION 3.0)
project(RyMPI3)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -std=c++1y -stdlib=libc++ -g -O3 \
  -Wall -Wextra \
  -Wno-missing-braces \
  -fcolor-diagnostics")

include_directories(Lib)
include_directories(/usr/local/include)

add_subdirectory(Examples)

install(DIRECTORY Lib/RyMPI 
  DESTINATION /usr/local/include
  FILES_MATCHING 
  PATTERN "*.hxx"
  PATTERN "*.hpp"
  )
