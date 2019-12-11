#include "./factory.hpp"

std::shared_ptr<LetterNode> create_letter_node(char letter)
{
    return std::make_shared<LetterNode>(letter);
}
