#pragma once

#include <memory>
#include "../Trie/Trie.hpp"
#include "../Board/Board.hpp"

void fill_trie(std::shared_ptr<Trie> trie);

void fill_trie(std::shared_ptr<Trie> trie, std::shared_ptr<Board> board);
