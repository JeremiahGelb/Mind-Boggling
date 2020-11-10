#include "factory.hpp"

std::shared_ptr<Solver> create_solver(std::shared_ptr<Board> board,
                                      std::shared_ptr<Trie> trie,
                                      bool allow_cycles) {
    return std::make_shared<Solver>(board, trie, allow_cycles);
}
