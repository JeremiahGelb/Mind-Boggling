
#pragma once

#include <memory>
#include <map>

class LetterNode
{
public:
    LetterNode(char letter)
    : letter_(letter)
    {
    }

    const std::map<char, std::shared_ptr<LetterNode>> & edges() const
    {
        return edges_;
    }

    const char & letter() const
    {
        return letter_;
    }

    void add_edge(std::shared_ptr<LetterNode> edge)
    {
        // TODO: make sure you don't add the same edge twice or yourself
        edges_.insert({edge->letter(), edge});
    }

    const std::string & word()
    {
        return word_;
    }

    void set_word(std::string & word)
    {
        word_ = word;
    }

private:
    const char letter_;
    std::map<char, std::shared_ptr<LetterNode>> edges_ = {};
    std::string word_ = ""; // set when letter is end of word
};

std::ostream & operator << (std::ostream & out, const LetterNode & b)
{
    out << "Letter is: ";
    out << b.letter() << std::endl;
    out << "Edges are: ";
    for([[maybe_unused]] const auto & [character, letter_node] : b.edges()){
        out << letter_node->letter() << " ";
    }
    out << std::endl;

    return out;
}