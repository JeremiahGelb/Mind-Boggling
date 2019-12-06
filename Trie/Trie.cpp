#include "Trie.hpp"

#include "../LetterNode/factory.hpp"
// #include <stdexcept>

Trie::Trie()
    : head_(create_letter_node('\0'))
{
}

void Trie::add_word(std::string word)
{
    auto current_node = head_;
    auto next_node = head_;

    for (const auto letter : word) {
        try
        {
            next_node = current_node->edges.at(letter);
        }
        catch (std::out_of_range & e)
        {
            next_node = create_letter_node(letter);
            current_node->add_edge(next_node);
        }
        current_node = next_node;
    }

    current_node->set_word(word);
}