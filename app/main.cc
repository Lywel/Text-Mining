#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include "trie.hh"
#include "backtrack_levenshtein.hh"

void search_aux(trie_set& res, const TrieNode& node, BacktrackLevenshtein& leven, uint16_t max_dist)
{
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

 //       std::cout << std::string(old_hay_size, ' ') << "-= '" << child.str << "'" << std::endl;
    }
}

trie_set search(const TrieNode& root, const std::string& word, uint16_t distance)
{
    trie_set res;
    BacktrackLevenshtein leven(word, distance);
    search_aux(res, root, leven, distance);
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

    TrieNode root("");
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
    // root.pretty_print(std::cout);
    loop(root, std::cin, std::cout);

    return 0;
}
