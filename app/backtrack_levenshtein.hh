#pragma once

#include <string>

class BacktrackLevenshtein
{
public:
    BacktrackLevenshtein(const std::string& word, uint16_t max_dist);
    ~BacktrackLevenshtein();
    uint16_t add(const std::string& str);
    uint16_t distance() const;
    void reset_hay(uint16_t size);
    uint16_t get_hay_size();

    char* get_hay() const;
    void debug() const;

private:
    char* needle;
    uint16_t needle_size;

    char* hay;
    uint16_t max_hay_size;
    uint16_t hay_size;

    uint16_t** dist;
};

