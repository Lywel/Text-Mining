set(GLOB HEADERS
  ../trie/trie.hh
  backtrack_levenshtein.hh
)

file(GLOB SRC
  ${HEADERS}
  ../trie/trie.cc
  backtrack_levenshtein.cc
  main.cc
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
add_executable(TextMiningApp ${SRC})
target_include_directories(TextMiningApp PUBLIC ../trie .)
target_link_libraries(TextMiningApp LINK_PUBLIC ${Boost_LIBRARIES} )
