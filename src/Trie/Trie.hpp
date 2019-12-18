#pragma once

#include <string>
#include <memory>
#include <vector>
// TODO(JeremiahGelb): get rid of relative path
#include "../LetterNode/factory.hpp"


class Trie {
 public:
    Trie();

    const std::shared_ptr<LetterNode> & head() const {
        return head_;
    }

    void add_word(const std::string & word);

    bool contains_word(const std::string & word) const;

    std::vector<std::shared_ptr<LetterNode>> preorder_node_list(const std::shared_ptr<LetterNode> & head);

 private:
    const std::shared_ptr<LetterNode> head_;
};

