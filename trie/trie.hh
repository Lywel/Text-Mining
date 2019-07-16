#include <map>
#include <vector>
#include <iostream>

class TrieNode
{
public:
    TrieNode(const std::string& str_)
        : str(str_) {};
    TrieNode(const std::string& str_, uint32_t occ_)
        : str(str_), occ(occ_) {};
    TrieNode(const std::string& str_, const std::vector<TrieNode>& child_)
        : str(str_), child(child_) {};
    TrieNode(const std::string& str_, uint32_t occ_, const std::vector<TrieNode>& child_)
        : str(str_), occ(occ_), child(child_) {};

    size_t len() const;
    void pretty_print(std::ostream& out) const;
    void marshal(std::ostream& out) const;

    template <class... Args>
    TrieNode* add_child(Args&&... args);

    std::string str;
    uint32_t occ = 0;
    std::vector<TrieNode> child;

private:
    void pretty_print_aux(std::ostream& out, int offset) const;
};
