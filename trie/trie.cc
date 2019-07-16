#include "trie.hh"

size_t TrieNode::len() const
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
