#pragma once

#include <unordered_set>
#include <map>
#include <memory>
#include <string>

#include "../LetterNode/LetterNode.hpp"

class Board {
 public:
    const std::map<char, std::unordered_set<std::shared_ptr<LetterNode>>> & tiles() {
        return tiles_;
    }

    void add_tile(std::shared_ptr<LetterNode> tile) {
        // TODO(JG): make sure they don't add themself
        try {
            auto tile_set = tiles_.at(tile->letter());
            tile_set.insert(tile);
        }
        catch (std::out_of_range e) {
            std::unordered_set<std::shared_ptr<LetterNode>> tile_set = {tile};
            tiles_.insert({tile->letter(), tile_set});
        }
    }

    bool word_in_board(const std::string & word) const;

 private:
    std::map<char, std::unordered_set<std::shared_ptr<LetterNode>>> tiles_;
    bool substring_possible_from_head(std::string substring,
                                      std::shared_ptr<LetterNode> head,
                                      std::unordered_set<std::shared_ptr<LetterNode>> & visited_nodes) const;
};
