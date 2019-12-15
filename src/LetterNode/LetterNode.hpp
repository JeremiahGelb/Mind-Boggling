
#pragma once

#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <vector>

// TODO(JG): some of these fucntions should get moved to the cpp

class LetterNode {
 public:
    explicit LetterNode(char letter)
    : letter_(letter) {
    }

    const std::map<char, std::vector<std::shared_ptr<LetterNode>>> & edges() const {
        return edges_;
    }

    const char & letter() const {
        return letter_;
    }

    void add_edge(std::shared_ptr<LetterNode> edge) {
        try {
            // TODO(JG): make sure you don't add the same edge twice or yourself
            auto letter_node_vector = edges_.at(edge->letter());
            letter_node_vector.push_back(edge);
        }
        catch (std::out_of_range & e) {
            std::vector<std::shared_ptr<LetterNode>> letter_node_vector = {edge};
            edges_.insert({edge->letter(), letter_node_vector});
        }
    }

    const std::string & name() const {
        return name_;
    }

    void set_name(const std::string & name) {
        name_ = name;
    }

 private:
    const char letter_;
    std::map<char, std::vector<std::shared_ptr<LetterNode>>> edges_ = {};
    std::string name_ = "";
    // in trie name can be set to represent a letter being th end of a word
    // in the gameboard the name can be set to represent the coordinates
};

std::ostream & operator << (std::ostream & out, const LetterNode & b);
