#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include "trie.hh"

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
    root.pretty_print(std::cout);
    return 0;
}

trie_set search(const TrieNode *root, std::string& str, uint8_t distance)
{
    /*trie_set res;
    std::queue<*TrieNode> queue;
    const auto *curr = root;
    uint8_t len = 0;

    do {

        for (auto& node: *curr.child)
        {
            if (levenstein_dist(node.str, str, len) =< distance)
            {
                queue.push(&node);
            }
        }

        len -= (*curr).len();
        curr = queue.pop();
        len += (*curr).len();

    } while(!queue.empty())

    return e;*/
    
    trie_set res;
    search_aux(res, root, "", str, distance);
}

void search_aux(trie_set& res, const TrieNode& cur, std::string& prev, std::string& str, uint8_t distance)
{
    uint8_t dist;
    std::string cur_str = prev + cur.str;

    if ((dist = levenstein_dist(cur_str, str.substr(0, cur_str.size()))) <= distance)
    {
        if (cur.occ && (cur_str.size() == str.size() || (dist = levenstein_dist(cur_str, str)) <= distance))
        {
            res.emplace(cur_str, cur.occ, dist);
        }
        else
        {
            for (auto& node : cur.child)
            {
                search_aux(res, node, cur_str, str, distance);
            }
        }
    }

}