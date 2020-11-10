#pragma once

#include <memory>
#include "Solver.hpp"

std::shared_ptr<Solver> create_solver(std::shared_ptr<Board> board,
                                      std::shared_ptr<Trie> trie,
                                      bool allow_cycles);
