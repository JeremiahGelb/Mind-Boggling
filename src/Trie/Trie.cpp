#include "Trie.hpp"

#include "../LetterNode/factory.hpp"

Trie::Trie()
    : head_(create_letter_node('\0')) {
}

void Trie::add_word(const std::string & word) {
    auto current_node = head_;
    auto next_node = head_;

    for (const auto letter : word) {
        try {
            next_node = current_node->edges().at(letter);
        }
        catch (std::out_of_range & e) {
            next_node = create_letter_node(letter);
            current_node->add_edge(next_node);
        }
        current_node = next_node;
    }

    current_node->set_name(word);
}

bool Trie::word_in_tree(const std::string & word) const {
    auto current_node = head_;
    auto next_node = head_;

    for (const auto letter : word) {
        try {
            next_node = current_node->edges().at(letter);
        }
        catch (std::out_of_range & e) {
            return false;
        }
        current_node = next_node;
    }

    if (current_node->name() != word) {
        throw std::runtime_error("word_in_tree: name doesn't match expected");
    }
    return true;
}
