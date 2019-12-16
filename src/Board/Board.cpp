#include "Board.hpp"

bool Board::word_in_board(const std::string & word) const {
    try {
        auto heads = tiles_.at(word[0]);

        if (word.length() == 1) {
            // if there are edges to the next letter and there is one letter left
            return true;
        }

        for (const auto & head : heads) {
            std::unordered_set<std::shared_ptr<LetterNode>> visited_nodes = {};
            if (substring_possible_from_head(word.substr(1), head, visited_nodes)) {
                return true;
            }
        }

        return false;
    }
    catch (std::out_of_range e) {
        return false;
    }
}

bool Board::substring_possible_from_head(std::string substring,
                                         std::shared_ptr<LetterNode> head,
                                         std::unordered_set<std::shared_ptr<LetterNode>> & visited_nodes) const {
    visited_nodes.insert(head);
    try {
        auto heads = head->edges().at(substring[0]);
        for (const auto & next_head : heads) {
            if (visited_nodes.count(next_head) > 0) {
                // don't go back to a node you have visited
                continue;
            }
            if (substring.length() == 1) {
                // if there are edges to the next letter and there is one letter left
                return true;
            }
            if (substring_possible_from_head(substring.substr(1), next_head, visited_nodes)) {
                return true;
            }
        }

        visited_nodes.erase(head);
        return false;
    }
    catch (std::out_of_range e) {
        visited_nodes.erase(head);
        return false;
    }
}
