// g++ -o char-count -O2 -std=c++17 -Wall main.cpp

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: char-count <file_name>\n"
            << "<file_name>: Name of file to analyse" << std::endl;

        return EXIT_SUCCESS;
    }

    std::ifstream file(argv[1], std::ios_base::binary | std::ios_base::in);

    if (!file.is_open())
    {
        std::cout << "Invalid file" << std::endl;

        return EXIT_FAILURE;
    }

    std::vector<std::pair<char, uint64_t>> characters;
    int file_size = 0;

    file.seekg(0, file.end);
    file_size = file.tellg();
    file.seekg(0, file.beg);

    std::cout << "File size: " << file_size << " byte" << std::endl;

    while (!file.eof())
    {
        char c = 0;
        file.read(&c, 1);

        if (file.eof())
            break;

        bool occured = false;
        std::size_t c_index = 0;

        for (std::size_t i = 0; i < characters.size(); i++)
            if (characters[i].first == c)
            {
                occured = true;
                c_index = i;
                break;
            }

        if (occured)
            characters[c_index].second++;
        else
        {
            std::pair<char, uint64_t> c_pair(c, 1);
            characters.push_back(c_pair);
        }
    }

    file.close();

    for (std::size_t i = 0; i < characters.size(); i++)
        for (std::size_t j = i + 1; j < characters.size(); j++)
        {
            if (characters[i].second > characters[j].second)
            {
                auto temp = characters[i];
                characters[i] = characters[j];
                characters[j] = temp;
            }
        }

    std::stringstream sstream;
    uint64_t characters_read = 0;
    for (auto &character : characters)
    {
        characters_read += character.second;

        sstream << std::setw(3) <<  (int) character.first << "  - " << character.second 
                << " (" << character.first << ")" << "\n";
    }
    sstream << characters_read << " characters read" << std::endl;
    std::cout << sstream.str();

    return EXIT_SUCCESS;
}
