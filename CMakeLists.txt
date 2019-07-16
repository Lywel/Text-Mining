cmake_minimum_required(VERSION 3.5)
project(textmining VERSION 1.0.0 LANGUAGES CXX)

# Cmake modules path
#list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

# Dependencies
find_package(Boost 1.55 REQUIRED COMPONENTS serialization)
find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)

include_directories( ${Boost_INCLUDE_DIR} )

# Doxygen config
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)

set(GLOB PROJECT_SOURCE_DIR
  app
  compiler
  trie
)

doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate doxygen HTML"
)

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -pedantic -O3 -std=c++2a" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -O3 -std=c++2a")

include_directories(trie)

add_subdirectory(compiler)
add_subdirectory(app)
