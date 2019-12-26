#include "TrieFiller.hpp"

#include <fstream>
#include <string>
#include <algorithm>

void fill_trie(std::shared_ptr<Trie> trie) {
    constexpr auto kDictionaryFileName = "/usr/share/dict/words";
    std::ifstream file(kDictionaryFileName);
    std::string word;
    if (!file) {
        std::cout << "Failed to open file: " << kDictionaryFileName << std::endl;
    }
    while (std::getline(file, word)) {
        std::transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c){ return std::tolower(c); });
        trie->add_word(word);
    }
}

void fill_trie(std::shared_ptr<Trie> trie, std::shared_ptr<Board> board) {
    // don't add word if the first letter isn't in the board
    constexpr auto kDictionaryFileName = "/usr/share/dict/words";
    std::ifstream file(kDictionaryFileName);
    std::string word;
    if (!file) {
        std::cout << "Failed to open file: " << kDictionaryFileName << std::endl;
    }
    while (std::getline(file, word)) {
        if (board->contains_letter(std::tolower(word[0]))) {
            std::transform(word.begin(), word.end(), word.begin(),
                [](unsigned char c){ return std::tolower(c); });
            trie->add_word(word);
        }
    }
}
