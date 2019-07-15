#include <iostream>
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include "trie.hh"

/**
 * @brief 
 *
 * @param root
 * @param word
 * @param offset
 */
void trie_insert(root_node root, std::string word, uint64_t offset)
{

}

/**
 * @brief Insert a word / occurence pair in the dict
 *
 * @param bin
 * @param word
 * @param occ
 *
 * @return The number of written bytes
 */
uint32_t dict_insert(std::ofstream& bin, const std::string& word, uint32_t occ)
{
    boost::archive::binary_oarchive oa{bin};

    oa & word;
    oa & occ;
    return 0;
}

/**
 * @brief 
 *
 * @param words
 * @param bin
 */
void compile(std::ifstream& words, std::ofstream& bin)
{
    std::string word;
    uint32_t occ;

    root_node root;
    while (words >> word >> occ) {
        uint32_t res = dict_insert(bin, word, occ);
        trie_insert(root, word, 0);
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr
            << "Usage: ./ref/TextMiningCompiler /path/to/word/freq.txt /path/to/output/dict.bin"
            << std::endl;
        return 1;
    }

    std::cout << "Size structure: 4" << std::endl;

    std::ifstream freq_file(argv[1], std::ifstream::in);
    if (!freq_file.is_open())
    {
        std::cout << "File not found: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream bin_file(argv[2], std::ifstream::out);
    if (!freq_file.is_open())
    {
        std::cout << "File not found: " << argv[1] << std::endl;
        return 1;
    }

    compile(freq_file, bin_file);

    return 0;
}

