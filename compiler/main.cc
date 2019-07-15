#include <iostream>
#include <fstream>
#include <algorithm>
#include "trie.hh"

/**
 * @brief 
 *
 * @param root
 * @param word
 * @param offset
 */
void trie_insert(trie_node& root, std::string word, uint64_t offset)
{
    std::cout << "insert_trie: " << word << std::endl;
    size_t cur = 0;
    trie_node& node = root;

    while (cur < word.size())
    {
        std::cout << "  char: " << cur << std::endl;
        const auto& next = std::find_if(node.child.begin(), node.child.end(),
            [&root, &word, &cur](const auto& n) -> bool
            {
                // If this node would have made the word too long
                if (n.len() > word.size() - cur)
                    return false;
                return n.label() == word[cur + n.len()];
            }
        );
        if (next == node.child.end()) {
            std::cout << "    no match found" << std::endl;

            /* no child fully matched
             * 1) check for partiel match
             *  - split the string on the partiely matched node
             *  - create a new node with the match (first half of the split)
             *      as a child of `node`
             *  - create a new node with the end of the new word as a child
             *      of this new node
             *  - attach the old splitted node, as a child of this same new node
             *      with only the second half of the split as its `.str`
             *
             *  2) if there is not even a partial match
             *   - just instert a new child on `node` with the end of the
             *      inserted word
             *      example: ``
             */

            // 2)
            std::string suffix = word.substr(cur);
            node.child.push_back(trie_node{suffix});
            cur += suffix.size();
        }
        else
        {
            node = *next;
            cur += node.len();
            std::cout << "    match of len:" << node.len() << " found" << std::endl;
        }
    }
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

    trie_node root;
    while (words >> word >> occ) {
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

