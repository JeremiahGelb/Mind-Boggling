
#pragma once

#include <memory>
#include <vector>

class BoardLetter
{
public:
    BoardLetter(char letter)
    : letter_(letter)
    {
    }

    const std::vector<std::shared_ptr<BoardLetter>> & edges() const
    {
        // TODO: make sure you don't add the same edge twice or yourself
        return edges_;
    }

    const char letter() const
    {
        return letter_;
    }

    void add_edge(std::shared_ptr<BoardLetter> edge)
    {
        edges_.push_back(edge);
    }

private:
    const char letter_;
    std::vector<std::shared_ptr<BoardLetter>> edges_ = {};
};

std::ostream & operator << (std::ostream & out, const BoardLetter & b) 
{ 
    out << "Letter is: ";
    out << b.letter() << std::endl;
    out << "Edges are: ";
    for(auto & edge : b.edges()){
        out << edge->letter() << " ";
    }
    out << std::endl;

    return out; 
} 