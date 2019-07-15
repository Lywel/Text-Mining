#include <map>
#include <vector>

struct trie_node
{
    char c;
    uint skipped_char;
    std::vector<trie_node> child;
};

struct root_node
{
    std::map<char, trie_node> child;
};
