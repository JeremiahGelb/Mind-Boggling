#pragma once

#include <memory>
#include <set>
#include <string>
#include "../Trie/Trie.hpp"
#include "../Board/Board.hpp"

class Solver {
 public:
    Solver(std::shared_ptr<Board> board,
           std::shared_ptr<Trie> trie,
           bool allow_cycles);

    const std::set<std::string> & words() {
       return words_;
    }

 private:
    bool allow_cycles_;
    const std::shared_ptr<Board> board_;
    const std::shared_ptr<Trie> trie_;
    std::set<std::string> words_;
};
