#include "Board.hpp"

bool Board::word_in_board(const std::string & word) const {
    try {
        auto heads = tiles_.at(word[0]);
        for (const auto & head : heads) {
            if (substring_possible_from_head(word.substr(1), head, {})) {
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
                                         std::unordered_set<std::shared_ptr<LetterNode>> visited_nodes) const {
    // TODO(JG) implement me
    return false;
}
