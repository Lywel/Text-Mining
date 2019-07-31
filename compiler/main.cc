#include <iostream>
#include <fstream>
#include "trie.hh"
#include <boost/archive/binary_oarchive.hpp>

size_t common_prefix_len(const std::string& str1, const std::string& str2)
{
    size_t len = 0;
    size_t n1 = str1.length(), n2 = str2.length();

    // Compare str1 and str2
    for (; len < n1 && len < n2; ++len)
        if (str1[len] != str2[len])
            break;

    return len;
}
/**
 * @brief 
 *
 * @param root
 * @param word
 * @param offset
 */
void trie_insert(TrieNode& root, std::string word, uint32_t occ)
{

    #ifdef DEBUG
    std::cout << std::endl << "insert(" << word << ")" << std::endl;
    #endif
    size_t cur = 0;
    TrieNode* node = &root;

    while (cur < word.size())
    {
        std::string suffix = word.substr(cur);
    #ifdef DEBUG
        std::cout << "  suffix: " << suffix << std::endl;
    #endif
            /* No child fully matched: Look for a partial match
             *
             * 1) partial match found
             *  - split the string on the partiely matched node
             *  - create a new node with the match (first half of the split)
             *      as a child of `node`
             *  - create a new node with the end of the new word as a child
             *      of this new node
             *  - attach the old splitted node, as a child of this same new node
             *      with only the second half of the split as its `.str`
             *
             *  2) no partial match
             *   - just instert a new child on `node` with the end of the
             *      inserted word
             */

            // Look for a partial match
            size_t match_id = 0;
            size_t match_len = 0;
            for (; match_id < node->child.size(); ++match_id)
            {
                match_len = common_prefix_len(node->child[match_id].str, suffix);
                if (match_len)
                    break;
            }

            if (!match_len)
            {
                // 2) no match at all
                // simple insert
                std::string suff = word.substr(cur);
                node->add_child(suff, occ);
                cur += suff.size();
    #ifdef DEBUG
                std::cout << "    leaf: " << suff << std::endl;
    #endif
            }
            else if (match_len == node->child[match_id].len())
            {
                if (match_len == suffix.size())
                {
                    // Full match found
                    std::string suff = word.substr(cur + match_len);
                    node->child[match_id].add_child(suff, occ);
                    cur += match_len + suff.size();
    #ifdef DEBUG
                    std::cout << "    leaf: " << suff << std::endl;
    #endif
                }
                else
                {
                    node = &(node->child[match_id]);
                    cur += match_len;
                }
            }
            else {
                // 1) Partial match found
                // split on match
                std::string pref = node->child[match_id].str.substr(0,match_len);
                std::string suff = node->child[match_id].str.substr(match_len);

                // create and append a prefix node
                TrieNode* new_node = node->add_child(pref);
    #ifdef DEBUG
                std::cout << "    node: " << pref << std::endl;
    #endif

                // append the end of the word to it
                new_node->add_child(suffix.substr(match_len), occ);
    #ifdef DEBUG
                std::cout << "      leaf: " <<  suffix.substr(match_len) << std::endl;
    #endif

                // attatch the end of the partially matched node
                new_node->add_child(suff, node->child[match_id].occ, node->child[match_id].child);
    #ifdef DEBUG
                std::cout << "      leaf: " <<  suff << std::endl;
    #endif

                // erase the old partially matched node
                node->child.erase(node->child.begin() + match_id);
    #ifdef DEBUG
                std::cout << "    erase: " << pref << suff << std::endl;
    #endif

                // Edit and relocation the partially matched node
                cur += suffix.size();
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

    TrieNode root("");
    while (words >> word >> occ) {
        trie_insert(root, word, occ);
    }

    #ifdef DEBUG
    root.pretty_print(std::cout);
    #endif

    // save data to archive
    {
        boost::archive::binary_oarchive oa(bin, boost::archive::no_header);
        oa << root;
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr
            << "Usage: " << argv[0]
            << " /path/to/word/freq.txt /path/to/output/dict.bin"
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

