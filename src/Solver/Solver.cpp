#include "Solver.hpp"
#include <deque>
#include <vector>
#include <utility>
#include <algorithm>
namespace {

struct SolvePosition {
    const std::shared_ptr<LetterNode> & trie_node_;
    const std::shared_ptr<LetterNode> & board_node_;
    std::vector<std::shared_ptr<LetterNode>> board_path_;
    SolvePosition(const std::shared_ptr<LetterNode> & trie_node,
                  const std::shared_ptr<LetterNode> & board_node,
                  const std::vector<std::shared_ptr<LetterNode>> && board_path)
    : trie_node_(trie_node)
    , board_node_(board_node)
    , board_path_(board_path) {
        board_path_.push_back(board_node);
    }
};

}  // namespace

Solver::Solver(std::shared_ptr<Board> board,
               std::shared_ptr<Trie> trie,
               bool allow_cycles)
: allow_cycles_(allow_cycles)
, trie_(trie)
, board_(board) {
    using WorkList = std::deque<SolvePosition>;
    const auto add_next_solve_positions_to_work_list = [this] (const SolvePosition & position,
                                                               WorkList & work_list) {
        const auto & trie_node = position.trie_node_;
        const auto & board_node = position.board_node_;

        const auto & board_edges_map = board_node->edges();
        for (const auto & [trie_letter, trie_edges] : trie_node->edges()) {
            try {
                const auto & board_edges = board_edges_map.at(trie_letter);
                const auto & trie_edge = *trie_edges.begin();
                const auto & board_path = position.board_path_;

                for (const auto & board_edge : board_edges) {
                    if (!allow_cycles_) {
                        if (std::find(board_path.begin(),
                                      board_path.end(),
                                      board_edge) != board_path.end()) {
                            continue;
                        }
                    }
                    work_list.emplace_back(SolvePosition(trie_edge, board_edge, std::move(board_path)));
                }
            } catch (std::out_of_range & e) {
                continue;
            }
        }
    };

    WorkList work_list;
    const auto trie_head = trie->head();
    for (const auto & [letter, letter_node_set] : board->tiles()) {
        for (const auto & board_edge : letter_node_set) {
            work_list.emplace_back(SolvePosition(trie_head, board_edge, {}));
        }
    }

    while (!work_list.empty()) {
        const auto & position = work_list.front();
        words_.insert(position.trie_node_->name());
        add_next_solve_positions_to_work_list(position, work_list);
        work_list.pop_front();
    }
}
