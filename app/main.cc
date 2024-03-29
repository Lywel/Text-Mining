#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include "trie.hh"
#include "backtrack_levenshtein.hh"

void search_exact(trie_set& res, const TrieNode* root, const std::string& word, size_t offset)
{
    /**
     * \fn void search_exact(trie_set& res, const TrieNode* root, const std::string& word, size_t offset)
     * \brief Search function for exact string (approx 0) 
     *
     * \param res, the set of results
     * \param root, the root of the trie we are searching in
     * \param word, the word we are looking for
     * \param offset, the current offset at which we are reading the word
     */
    // iterate on child
    for (const auto& child: (*root).child)
    {
        auto child_len = child.str.length();
        // make substring without copying
        auto sub_str = std::string_view(word.data() + offset, child_len);
        // if we arrive at a ending leaf, and we're at the end of the word, add the word
        if (child_len == 0 && word.length() == offset)
        {
            res.emplace(word, child.occ, 0);
            return;
        }
        // compare the strings
        if (sub_str.length() && child.str == sub_str)
        {
            if (child.occ && (offset + child_len) == word.length())
            {
                res.emplace(word, child.occ, 0);
                return;
            }
            // re iterate with current node as root
            search_exact(res, &child, word, offset + child.str.length());
            break;
        }
    }
}

void search_aux(trie_set& res, const TrieNode& node, BacktrackLevenshtein& leven, uint16_t max_dist)
{
    /**
     * \fn void search_aux(trie_set& res, const TrieNode& node, BacktrackLevenshtein& leven, uint16_t max_dist)
     * \brief Search function for string with approx 
     *
     * \param res, the set of results
     * \param root, the root of the trie we are searching in
     * \param word, the word we are looking for
     * \param max_dist, levenstein distance
     */
    for (const auto& child : node.child)
    {
        uint16_t old_hay_size = leven.get_hay_size();

        uint16_t dist = leven.add(child.str);
        if (dist <= 2 * max_dist)
        {
            if (child.occ && leven.distance() <= max_dist)
                res.emplace(std::string(leven.get_hay(), leven.get_hay_size()), child.occ, leven.distance());
            search_aux(res, child, leven, max_dist);
        }

        leven.reset_hay(old_hay_size);
    }
}

trie_set search(const TrieNode& root, const std::string& word, uint16_t distance)
{
    /**
     * \fn trie_set search(const TrieNode& root, const std::string& word, uint16_t distance)
     * \brief Dispatch between search approx 0 and search with approx > 0
     *
     * \param root, the root of the trie we are searching in
     * \param string, the word we are looking for
     * \param distance, levenstein distance
     */
    trie_set res;
    if (distance)
    {
        BacktrackLevenshtein leven(word, distance);
        search_aux(res, root, leven, distance);
    }
    else
        search_exact(res, &root, word, 0);

    return res;
}

void loop(const TrieNode& root, std::istream& words, std::ostream& out)
{
    std::string _;
    std::string word;
    uint16_t distance;

    while (words >> _ >> distance >> word)
    {
        std::string sep;
        const trie_set& results = search(root, word, distance);

        out << "[";
        for (const auto& result : results)
        {
            out << sep << result;
            sep = ",";
        }
        out << "]" << std::endl;
    }
}


int main(int argc, char** argv) {
    if (argc < 2)
    {
        std::cerr
            << "Usage: " << argv[0] << " /path/to/dict.bin"
            << std::endl;
        return 1;
    }
    TrieNode root;
    {
        std::ifstream bin_file(argv[1], std::ifstream::in);
        if (!bin_file.is_open())
        {
            std::cout << "File not found: " << argv[1] << std::endl;
            return 1;
        }
        boost::archive::binary_iarchive ia(bin_file, boost::archive::no_header);
        ia >> root;
    }
    //root.pretty_print(std::cout);
    loop(root, std::cin, std::cout);

    return 0;
}
