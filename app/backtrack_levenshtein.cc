#include "backtrack_levenshtein.hh"
#include <cstring>
#include <algorithm>
#include <iostream>

BacktrackLevenshtein::BacktrackLevenshtein(const std::string& word, uint16_t max_dist)
{
    needle_size = word.size();
    needle = new char[needle_size];
    strncpy(needle, word.c_str(), needle_size);

    max_hay_size = word.size() + max_dist;
    hay_size = 0;
    hay = new char[max_hay_size];

    // Initialize the levenstein table
    dist = new uint16_t*[max_hay_size + 1];
    for (uint16_t i = 0; i <= max_hay_size; ++i)
    {
        dist[i] = new uint16_t[word.size() + 1];
        dist[i][0] = i;
    }

    for (uint16_t j = 0; j <= needle_size; ++j)
        dist[0][j] = j;
}

BacktrackLevenshtein::~BacktrackLevenshtein()
{
    delete needle;
    delete hay;

    for (int i = 0; i <= max_hay_size; ++i)
        delete dist[i];
    delete dist;
}

uint16_t BacktrackLevenshtein::add(const std::string& str)
{
    // If the number of letters added makes a word longer than the maximum
    // possible size then we return an the maximum distance (-1)
    if (hay_size + str.size() > max_hay_size)
        return -1;

    // Increment the new hay
    strncpy(hay + hay_size, str.c_str(), str.size());

    // Update the levenstein table
    for (uint16_t i = hay_size + 1; i <= hay_size + str.size(); ++i)
    {
        for (uint16_t j = 1; j <= needle_size; ++j)
        {
            uint16_t diff = (hay[i-1] != needle[j-1]);

            uint16_t sup_dist = dist[i-1][j] + 1; // Suppression
            uint16_t ins_dist = dist[i][j-1] + 1; // Insertion
            uint16_t sub_dist = dist[i-1][j-1] + diff; // Substitution

            dist[i][j] = std::min({sup_dist, ins_dist, sub_dist});

            // Transposition
            if (i > 1 && j > 1 && hay[i-1] == needle[j-2] && hay[i-2] == needle[j-1])
                dist[i][j] = std::min(dist[i][j], (uint16_t)(dist[i-2][j-2] + diff));
        }
    }

    // Increment current hay size
    hay_size += str.size();



    return dist[hay_size][std::min(hay_size, needle_size)];
    // Not the real dist tho => leaf dist = dist[hay_size, needle_size]
}

uint16_t BacktrackLevenshtein::distance() const
{
    return dist[hay_size][needle_size];
}


void BacktrackLevenshtein::reset_hay(uint16_t size)
{
    hay_size = size;
}

uint16_t BacktrackLevenshtein::get_hay_size()
{
    return hay_size;
}

char* BacktrackLevenshtein::get_hay() const
{
    return hay;
}

void BacktrackLevenshtein::debug() const
{
    for (uint16_t i = 0; i <= hay_size; ++i)
    {
        if (!i)
        {
            std::cout << "    ";
            for (uint16_t j = 0; !i && j < needle_size; ++j)
                std::cout << needle[j] << " ";
            std::cout << std::endl;
        }
        for (uint16_t j = 0; j <= needle_size; ++j)
        {
            if (!j)
            {
                if (i > 0)
                    std::cout << hay[i-1] << " ";
                else
                    std::cout << "  ";
            }
            std::cout << dist[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
