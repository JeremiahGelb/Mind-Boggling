#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../LetterNode/LetterNode.hpp"

class Board {
 public:
    const std::vector<std::shared_ptr<LetterNode>> & tiles() {
        return tiles_;
    }

    void add_tile(std::shared_ptr<LetterNode> tile) {
        tiles_.push_back(tile);
    }

    bool word_in_board(const std::string & word) const;

 private:
    // TODO(JG) this could be a map<char, vector<letterNode> > for faster search
    std::vector<std::shared_ptr<LetterNode>> tiles_;
};
