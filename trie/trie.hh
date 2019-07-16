#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

class TrieNode
{
public:
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
        ar & str;
        ar & occ;
        ar & child;
    }

    void pretty_print_aux(std::ostream& out, int offset) const;
};
