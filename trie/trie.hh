#include <map>
#include <vector>

struct trie_node
{
    char label() const
    {
        return str[str.size()-1];
    }
    size_t len() const
    {
        return str.size() - 1;
    }
    std::string str;
    std::vector<trie_node> child;
};
