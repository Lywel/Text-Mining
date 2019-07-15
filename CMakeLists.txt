cmake_minimum_required(VERSION 3.5)
project(textmining VERSION 1.0.0 LANGUAGES CXX)

# Cmake modules path
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

# Dependencies
# find_package(Boost 1.55 REQUIRED COMPONENTS regex)

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -pedantic -Ofast -DNO_BZIP2" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -Ofast -DNO_BZIP2")

add_subdirectory(compiler)
add_subdirectory(app)
