#include "Trie.hpp"

#include <iostream>
#include <utility>
#include "../LetterNode/factory.hpp"

Trie::Trie()
: head_(create_letter_node('\0')) {
    head_->set_name("HEAD");
}

// TODO(Jg): constexpr auto first_child = 0 is ugly. Figure out something better

void Trie::add_word(const std::string & word) {
    auto current_node = head_;
    auto next_node = head_;

    for (const auto letter : word) {
        try {
            // Correctly formed trie should only have one child for each letter
            constexpr auto first_child = 0;
            next_node = current_node->edges().at(letter)[0];
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
            // Correctly formed trie should only have one child for each letter
            constexpr auto first_child = 0;
            next_node = current_node->edges().at(letter)[first_child];
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

std::vector<std::shared_ptr<LetterNode>> Trie::preorder_node_list(const std::shared_ptr<LetterNode> & head) {
    // TODO(JG): test that the list is also preorder
    std::vector<std::shared_ptr<LetterNode>> node_list = {head};
    std::cout << *head << std::endl;

    for ([[maybe_unused]] const auto & [character, letter_node_vector] : head->edges()) {
        // Correctly formed trie should only have one child for each letter
        constexpr auto first_child = 0;
        auto child_node_list = preorder_node_list(letter_node_vector[0]);
        std::move(child_node_list.begin(), child_node_list.end(), std::back_inserter(node_list));
    }

    return node_list;
}
