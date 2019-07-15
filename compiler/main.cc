#include <iostream>
#include <fstream>
#include <algorithm>
#include "trie.hh"
#include <iomanip>

void print_trie_(const trie_node& t, int offset)
{
    std::cout
        <<  std::string(offset, ' ')
        << "└"
        << " " << t.str << std::endl;

    for (const trie_node& c : t.child)
        print_trie_(c, offset + 2);
}

void print_trie(const trie_node& t)
{
    for (const trie_node& c : t.child)
        print_trie_(c, 0);
}

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
void trie_insert(trie_node& root, std::string word)
{
    std::cout << std::endl << "insert(" << word << ")" << std::endl;
    size_t cur = 0;
    trie_node* node = &root;

    while (cur < word.size())
    {
        std::string suffix = word.substr(cur);
        std::cout << "  suffix: " << suffix << std::endl;

        // Look for a full match
        const auto& next = std::find_if(node->child.begin(), node->child.end(),
            [&root, &word, &cur](const auto& n) -> bool
            {
                // If this node would have made the word too long
                if (n.len() > word.size() - cur)
                    return false;
                return n.label() == word[cur + n.len()];
            }
        );

        if (next == node->child.end()) {
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
            if (match_len) {
                // 1) Partial match found
                // split on match
                std::string pref = node->child[match_id].str.substr(0,match_len);
                std::string suff = node->child[match_id].str.substr(match_len);

                // create a prefix node
                trie_node new_node{pref};
                std::cout << "    node: " << pref << std::endl;

                // append the end of the word to it
                new_node.child.push_back(trie_node{suffix.substr(match_len)});
                std::cout << "      leaf: " <<  suffix.substr(match_len) << std::endl;

                // attatch the end of the partially matched node
                new_node.child.push_back(trie_node{suff, node->child[match_id].child});
                std::cout << "      leaf: " <<  suff << std::endl;

                // append the new node
                node->child.push_back(new_node);

                // erase the old partially matched node
                node->child.erase(node->child.begin() + match_id);
                std::cout << "    erase: " << pref << suff << std::endl;

                // Edit and relocation the partially matched node
                cur += suffix.size();
            }
            else
            {
                // 2) Simple insert
                std::string suffix = word.substr(cur);
                node->child.push_back(trie_node{suffix});
                cur += suffix.size();
                std::cout << "    leaf: " << suffix << std::endl;
            }
        }
        else
        {
            node = &(*next);
            cur += node->len();
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
        trie_insert(root, word);
        print_trie(root);
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

