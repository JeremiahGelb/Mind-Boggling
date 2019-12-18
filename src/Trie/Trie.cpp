#include "Trie.hpp"

#include <iostream>
#include <utility>
#include "../LetterNode/factory.hpp"

Trie::Trie()
: head_(create_letter_node('\0')) {
    head_->set_name("HEAD");
}

void Trie::add_word(const std::string & word) {
    auto current_node = head_;
    auto next_node = head_;

    for (const auto letter : word) {
        try {
            // Correctly formed trie should only have one child for each letter
            next_node = *(current_node->edges().at(letter).begin());
        }
        catch (std::out_of_range & e) {
            next_node = create_letter_node(letter);
            current_node->add_edge(next_node);
        }
        current_node = next_node;
    }

    current_node->set_name(word);
}

bool Trie::contains_word(const std::string & word) const {
    auto current_node = head_;
    auto next_node = head_;

    for (const auto letter : word) {
        try {
            // Correctly formed trie should only have one child for each letter
            next_node = *(current_node->edges().at(letter).begin());
        }
        catch (std::out_of_range & e) {
            return false;
        }
        current_node = next_node;
    }

    if (current_node->name() != word) {
        throw std::runtime_error("contains_word: name doesn't match expected");
    }
    return true;
}

std::vector<std::shared_ptr<LetterNode>> Trie::preorder_node_list(const std::shared_ptr<LetterNode> & head) {
    // TODO(JG): test that the list is also preorder
    std::vector<std::shared_ptr<LetterNode>> node_list = {head};
    std::cout << *head << std::endl;

    for ([[maybe_unused]] const auto & [character, letter_node_set] : head->edges()) {
        // Correctly formed trie should only have one child for each letter
        auto child_node_list = preorder_node_list(*(letter_node_set.begin()));
        std::move(child_node_list.begin(), child_node_list.end(), std::back_inserter(node_list));
    }

    return node_list;
}
