#pragma once

#include "BoardLetter.hpp"
#include <memory>

std::shared_ptr<BoardLetter> create_board_letter(char letter)
{
    return std::make_shared<BoardLetter>(letter);
}