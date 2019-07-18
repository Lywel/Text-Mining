#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include "trie.hh"

int mini(int a, int b, int c){
    return(min(a, min(b,c)));
}

uint16_t levenstein_dist(const std::string& s1, const std::string& s2)
{
    int size1 = s1.size(), size2 = s2.size();
    int suppr_dist, insert_dist, subs_dist, val;
    int* dist = new int[(size1 + 1) * (size2 + 1)];

    for (int i = 0; i < size1 + 1; ++i)
        dist[(size2 + 1) * i] = i;

    for (int j = 0; j < size2 + 1; ++j)
        dist[j] = j;

    for (int i = 1; i < size1 + 1; ++i)
    {
      for (int j = 1; j < size2 + 1; ++j)
      {
        suppr_dist = dist[(size2 + 1) * (i - 1) + j] + 1;
        insert_dist = dist[(size2 + 1) * i + j - 1] + 1;
        subs_dist = dist[(size2 + 1) * (i - 1) + j - 1];
        
        if (word1[i-1] != word2[j-1])
          subs_dist += 1;
        
        val = mini(suppr_dist, insert_dist, subs_dist);
        if(((i>=2) && (j>=2)) && ((word1[i-1]==word2[j-2]) && (word1[i-2]==word2[j-1])))
              val = std::min(dist[(size2+1)*(i-2)+j-2]+1, val);
          dist[(size2+1)*i+j] = val;
      }
    }

    int res = dist[(size1+1)*(size2+1) - 1];
    delete dist;
    return(res);
}

void search_aux(trie_set& res, const TrieNode& node, const std::string& word,
        const std::string acc, uint16_t max_dist)
{
    if (word.size() + max_dist < acc.size())
        return;

    for (const auto& child : node.child)
    {
        const std::string cur_str = acc + child.str;
        if (child.occ)
        {
            uint16_t dist = levenstein_dist(word, cur_str);

            if (dist <= max_dist)
            {
                res.emplace(cur_str, child.occ, dist);
                if (!max_dist)
                    return;
            }
        }
        else
        {
            search_aux(res, child, word, cur_str, max_dist);
        }
    }
}

trie_set search(const TrieNode& root, const std::string& word, uint16_t distance)
{
    trie_set res;
    search_aux(res, root, word, "", distance);
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
    std::string a("martin");
    std::string b("gratin");
    std::cout << "|martin/gratin| = " << levenstein_dist(a, b) << std::endl;
    exit(0);
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
