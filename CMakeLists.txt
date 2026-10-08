cmake_minimum_required(VERSION 3.16)

project(DSA LANGUAGES C CXX)

set( CMAKE_C_STANDARD 23 )
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

include_directories( ${PROJECT_SOURCE_DIR}/include )
add_subdirectory( S1 )
add_subdirectory( S2 )
