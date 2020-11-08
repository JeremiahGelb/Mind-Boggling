#include "Solver.hpp"
#include <deque>
#include <iostream>
namespace {

struct SolvePosition {
    const std::shared_ptr<LetterNode> & trie_node_;
    const std::shared_ptr<LetterNode> & board_node_;
    SolvePosition(const std::shared_ptr<LetterNode> & trie_node,
                  const std::shared_ptr<LetterNode> & board_node)
    : trie_node_(trie_node)
    , board_node_(board_node) {
        // std::cout << "SolvePostition Constructor" << std::endl;
    }
};

}  // namespace

Solver::Solver(std::shared_ptr<Board> board, std::shared_ptr<Trie> trie)
: trie_(trie)
, board_(board) {
    // std::cout << "Enter Solver Constructor" << std::endl;
    using WorkList = std::deque<SolvePosition>;
    const auto add_next_solve_positions_to_work_list = [] (const SolvePosition & position,
                                                           WorkList & work_list) {
        const auto & trie_node = position.trie_node_;
        const auto & board_node = position.board_node_;
        // std::cout << "----------------------------------" << std::endl;
        // std::cout << "investigating trie_node: " << trie_node->letter()
        //           << " board node: " << board_node->letter() << std::endl;

        const auto & board_edges_map = board_node->edges();
        for (const auto & [trie_letter, trie_edges] : trie_node->edges()) {
            try {
                // std::cout << "trying trie_letter: " << trie_letter << std::endl;
                const auto & board_edges = board_edges_map.at(trie_letter);
                // std::cout << "board had: " << board_edges.size() << std::endl;
                const auto & trie_edge = *trie_edges.begin();
                for (const auto & board_edge : board_edges) {
                    work_list.emplace_back(SolvePosition(trie_edge, board_edge));
                }
            } catch (std::out_of_range & e) {
                // std::cout << "board didn't have it" << std::endl;
                continue;
            }
        }
        // std::cout << "------------------------------" << std::endl;
    };

    WorkList work_list;
    const auto trie_head = trie->head();
    // std::cout << "Filling from board" << std::endl;
    for (const auto & [letter, letter_node_set] : board->tiles()) {
        for (const auto & board_edge : letter_node_set) {
            work_list.emplace_back(SolvePosition(trie_head, board_edge));
        }
    }

    // std::cout << "Starting Solve" << std::endl;
    while (!work_list.empty()) {
        const auto & position = work_list.front();
        words_.insert(position.trie_node_->name());
        add_next_solve_positions_to_work_list(position, work_list);
        work_list.pop_front();
    }
}
