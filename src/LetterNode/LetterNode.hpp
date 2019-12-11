
#pragma once

#include <memory>
#include <map>
#include <string>
#include <iostream>

class LetterNode {
 public:
    explicit LetterNode(char letter)
    : letter_(letter) {
    }

    const std::map<char, std::shared_ptr<LetterNode>> & edges() const {
        return edges_;
    }

    const char & letter() const {
        return letter_;
    }

    void add_edge(std::shared_ptr<LetterNode> edge) {
        // TODO(JG): make sure you don't add the same edge twice or yourself
        edges_.insert({edge->letter(), edge});
    }

    const std::string & name() const {
        return name_;
    }

    void set_name(const std::string & name) {
        name_ = name;
    }

 private:
    const char letter_;
    std::map<char, std::shared_ptr<LetterNode>> edges_ = {};
    std::string name_ = "";
    // in trie name can be set to represent a letter being th end of a word
    // in the gameboard the name can be set to represent the coordinates
};

std::ostream & operator << (std::ostream & out, const LetterNode & b);
