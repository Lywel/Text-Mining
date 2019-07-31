cmake_minimum_required(VERSION 3.5)
project(textmining VERSION 1.0.0 LANGUAGES CXX)

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

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)

# Flags
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-ggdb -O2")
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Ofast -ffloat-store -ffast-math -fno-rounding-math -fno-signaling-nans -fcx-limited-range -fno-math-errno -funsafe-math-optimizations -fassociative-math -freciprocal-math -ffinite-math-only -fno-signed-zeros -fno-trapping-math -frounding-math -fsingle-precision-constant -fcx-fortran-rules")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Ofast -ffloat-store -ffast-math -fno-rounding-math -fno-signaling-nans -fcx-limited-range -fno-math-errno -funsafe-math-optimizations -fassociative-math -freciprocal-math -ffinite-math-only -fno-signed-zeros -fno-trapping-math -frounding-math -fsingle-precision-constant -fcx-fortran-rules")


add_subdirectory(compiler)
add_subdirectory(app)
