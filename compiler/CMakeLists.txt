set(GLOB HEADERS
  *.hh
  ../trie/*.hh
)

file(GLOB SRC
  ${HEADERS}
  *.cc
  ../trie/*.cc
)

include_directories(../trie)

add_executable(compiler ${SRC})
target_link_libraries(compiler LINK_PUBLIC ${Boost_LIBRARIES} )
