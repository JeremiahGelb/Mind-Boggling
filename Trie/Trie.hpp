#pragma once

// TODO: get rid of relative path
#include "../LetterNode/LetterNode.hpp"

class Trie {
public:
    const std::shared_ptr<LetterNode> & head() {
        return head_;
    }

    void add_word(std::string word);

private:
    const std::shared_ptr<LetterNode> head_;
}