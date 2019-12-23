#pragma once

#include <memory>
#include "../Trie/Trie.hpp"
#include "../Board/Board.hpp"

class Solver {
 public:
    Solver(std::shared_ptr<Board> board, std::shared_ptr<Trie> trie);

 private:
    const std::shared_ptr<Board> board_;
    const std::shared_ptr<Trie> trie_;
};
