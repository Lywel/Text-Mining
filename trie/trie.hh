#include <map>
#include <vector>

class trie_node
{
    char c;
    uint skipped_char;
    uint offset; 
    std::vector<trie_node> child;
};

struct root_node
{
    std::map<char, trie_node> child;
};
