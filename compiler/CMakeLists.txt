set(GLOB HEADERS
  ../trie/trie.hh
)

file(GLOB SRC
  ${HEADERS}
  ../trie/trie.cc
  main.cc
)

add_executable(TextMiningCompiler ${SRC})
target_include_directories(TextMiningCompiler PUBLIC ../trie)
target_link_libraries(TextMiningCompiler LINK_PUBLIC ${Boost_LIBRARIES} )
