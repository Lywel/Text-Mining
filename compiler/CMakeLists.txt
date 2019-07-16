set(GLOB HEADERS
  ../trie/trie.hh
)

file(GLOB SRC
  ${HEADERS}
  ../trie/trie.cc
  main.cc
)

add_executable(compiler ${SRC})
target_include_directories(compiler PUBLIC ../trie)
target_link_libraries(compiler LINK_PUBLIC ${Boost_LIBRARIES} )
