#pragma once

#include <string>
#include <memory>
// TODO(JeremiahGelb): get rid of relative path
#include "../LetterNode/LetterNode.hpp"


class Trie {
public:
    Trie();

    const std::shared_ptr<LetterNode> & head() const {
        return head_;
    }

    void add_word(const std::string & word);

    bool word_in_tree(const std::string & word) const;

private:
    const std::shared_ptr<LetterNode> head_;
};

// TODO(JeremiahGelb): recursive function to print it TrieOrder (haha)
