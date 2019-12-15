#pragma once

#include <vector>
#include <map>
#include <memory>
#include <string>

#include "../LetterNode/LetterNode.hpp"

class Board {
 public:
    const std::map<char, std::vector<std::shared_ptr<LetterNode>>> & tiles() {
        return tiles_;
    }

    void add_tile(std::shared_ptr<LetterNode> tile) {
        // TODO(JG): make sure they don't add the same edge twice or themself
        try {
            auto tile_vector = tiles_.at(tile->letter());
            tile_vector.push_back(tile);
        }
        catch (std::out_of_range e) {
            std::vector<std::shared_ptr<LetterNode>> tile_vector = {tile};
            tiles_.insert({tile->letter(), tile_vector});
        }

    }

    bool word_in_board(const std::string & word) const;

 private:
    std::map<char, std::vector<std::shared_ptr<LetterNode>>> tiles_;
};
