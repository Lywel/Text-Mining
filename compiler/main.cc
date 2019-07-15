#include <iostream>
#include <fstream>

void compile(std::ifstream& words, std::ofstream& bin)
{
    std::string word;
    uint32_t occ;

    while (words >> word >> occ) {

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

