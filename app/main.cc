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
