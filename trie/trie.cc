#include "trie.hh"

inline size_t TrieNode::len() const
{
    return str.size();
}

void TrieNode::pretty_print(std::ostream& out) const
{
    for (const TrieNode& c : child)
        c.pretty_print_aux(out, 0);
}

void TrieNode::pretty_print_aux(std::ostream& out, int offset) const
{
    out << std::string(offset, ' ') << "└ " << str;

    if (occ)
        out << " (" << occ << ")";

    out << std::endl;

    for (const TrieNode& c : child)
        c.pretty_print_aux(out, offset + 2);
}

void TrieNode::marshal(std::ostream& out) const
{

}

template <class... Args>
TrieNode* TrieNode::add_child(Args&&... args)
{
    return &(child.emplace_back(std::forward<Args>(args)...));
}
