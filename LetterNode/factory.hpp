#pragma once

#include "LetterNode.hpp"
#include <memory>

std::shared_ptr<LetterNode> create_letter_node(char letter)
{
    return std::make_shared<LetterNode>(letter);
}