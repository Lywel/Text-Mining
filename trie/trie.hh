#include <map>
#include <vector>

struct trie_node
{
    size_t len() const
    {
        return str.size();
    }
    std::string str;
    std::vector<trie_node> child;
    uint32_t occ = 0;
};
