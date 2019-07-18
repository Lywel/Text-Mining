#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <set>

class TrieNode
{
public:
    TrieNode() {};
    TrieNode(const std::string& str_)
        : str(str_) {};
    TrieNode(const std::string& str_, uint32_t occ_)
        : str(str_), occ(occ_) {};
    TrieNode(const std::string& str_, const std::vector<TrieNode>& child_)
        : str(str_), child(child_) {};
    TrieNode(const std::string& str_, uint32_t occ_, const std::vector<TrieNode>& child_)
        : str(str_), occ(occ_), child(child_) {};

    size_t len() const;
    void pretty_print(std::ostream& out) const;

    template <class... Args>
    TrieNode* add_child(Args&&... args)
    {
        return &(child.emplace_back(std::forward<Args>(args)...));
    }

    std::string str;
    uint32_t occ = 0;
    std::vector<TrieNode> child;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        (void)version;
        ar & str;
        ar & occ;
        ar & child;
    }

    void pretty_print_aux(std::ostream& out, int offset) const;
};

struct result
{
    result(const std::string& str_, uint32_t freq_, uint16_t distance_)
        : str(str_), freq(freq_), distance(distance_) {};
    std::string str;
    uint32_t freq;
    uint16_t distance;
    friend std::ostream& operator<<(std::ostream &out, const result &r)
    {
        out << "{"
            << "\"word\":\"" << r.str << "\","
            << "\"freq\":" << r.freq << ","
            << "\"distance\":" << r.distance << "}";
        return out;
    }
};

struct result_compare
{
    bool operator() (const result& lhs, const result& rhs) const 
    {
        return (lhs.distance < rhs.distance)
            || ((lhs.distance == rhs.distance) && lhs.freq > rhs.freq)
            || ((lhs.freq == rhs.freq) && lhs.str < rhs.str);
    }
};

typedef std::set<result, result_compare> trie_set;
