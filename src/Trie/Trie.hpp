#pragma once

// TODO: get rid of relative path
#include "../LetterNode/LetterNode.hpp"
#include <string>

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

// TODO: recursive function to print it TrieOrder (haha)