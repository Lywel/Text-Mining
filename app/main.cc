#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include "trie.hh"

uint16_t levenstein_dist(const std::string& s1, const std::string& s2)
{
  size_t size1 = s1.size();
  size_t size2 = s2.size();
  size_t d[size1 + 1][size2 + 1];
  for (int i = 0; i <= size1; i ++)
    d[i][0] = i;
  for (int i = 0; i <= size2; i ++)
    d[0][i] = i;

  int cost = 0;
  for (int i = 1; i <= size1; i ++)
    for (int j = 1; j <= size2; j ++)
    {
      cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1 ;
      if ( (i > 1) && (j > 1) && (s1[i] == s2[j - 1]) && (s1[i - 1] == s2[j]))
      {
        size_t a = std::min(d[i - 1][j], d[i][j - 1] + 1);
        size_t b = std::min(d[i][j] + cost, d[i - 2][j - 2]);
        d[i][j] = std::min(a, b);
      }
      else
      {
        d[i][j] = std::min(std::min(d[i][j -1] + 1, d[i - 1][j] + 1), d[i - 1][j - 1] + cost);
      }
    }
  return d[size1][size2];
}

void search_aux(trie_set& res, const TrieNode& cur, const std::string& prev, const std::string& str, uint16_t distance)
{
    uint16_t dist;
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

trie_set search(const TrieNode& root, const std::string& str, uint16_t distance)
{
    trie_set res;
    search_aux(res, root, root.str, str, distance);
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
