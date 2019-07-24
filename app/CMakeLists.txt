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

add_executable(app ${SRC})
target_include_directories(app PUBLIC ../trie .)
target_link_libraries(app LINK_PUBLIC ${Boost_LIBRARIES} )
