#include <map>
#include <string>
#include <variant>
#include <vector>

struct trie_node
{
    char c;
    uint skipped_char;
};

class trie
{
    trie_node node;
    std::vector<trie_node> child;
};

struct root_node
{
    std::map<char, trie> child;
};
