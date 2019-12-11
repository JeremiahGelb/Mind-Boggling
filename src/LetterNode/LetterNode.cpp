#include "LetterNode.hpp"

std::ostream & operator << (std::ostream & out, const LetterNode & b) {
    out << "Name_ is: " << b.name() << std::endl;
    out << "Letter is: " << b.letter() << std::endl;
    out << "Edges are: ";
    for ([[maybe_unused]] const auto & [character, letter_node] : b.edges()) {
        out << letter_node->letter() << " ";
    }
    out << std::endl;

    return out;
}
