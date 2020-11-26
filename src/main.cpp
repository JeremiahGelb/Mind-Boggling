#include <iostream>
#include "LetterNode/factory.hpp"
#include "Trie/factory.hpp"
#include "Board/factory.hpp"
#include "TrieFiller/TrieFiller.hpp"
#include "Solver/factory.hpp"
#include "timeit/timeit.hpp"

void manual_test() {
    constexpr auto kTestLetterNode = true;
    constexpr auto kTestTrie = true;
    constexpr auto kTestBoard = true;
    constexpr auto kTestTrieFiller = false;
    constexpr auto kTestTimeIt = false;
    constexpr auto kTestSolver = true;

    if (kTestLetterNode) {
        std::cout << "Testing LetterNode" << std::endl;
        auto h = create_letter_node('h');
        auto i = create_letter_node('i');

        h->set_name("test_h");
        i->set_name("test_i");

        h->add_edge(i);
        i->add_edge(h);

        std::cout << "---------------" << std::endl;
        std::cout << *h;
        std::cout << "---------------" << std::endl;
        std::cout << *i;
        std::cout << "---------------" << std::endl;
    }

    if (kTestTrie) {
        std::cout << "Testing Trie"  << std::endl;
        auto trie = create_trie();
        trie->add_word("cat");
        trie->add_word("cap");
        trie->add_word("bat");

        if (trie->contains_word("cat")) {
            std::cout << "cat was in tree!" << std::endl;
        }


        if (trie->contains_word("dog")) {
            std::cout << "Dog was in tree?" << std::endl;
        } else {
            std::cout << "As expected, dog was not in tree" << std::endl;
        }


        auto node = trie->head();
        node = *node->edges().at('c').begin();
        node = *node->edges().at('a').begin();
        node = *node->edges().at('t').begin();
        node->set_name("catt");
        try {
            trie->contains_word("cat");
        }
        catch (std::runtime_error e) {
            std::cout << "bad name caught as expected" << std::endl;
        }
        node->set_name("cat");
        trie->contains_word("cat");

        std::cout << "--------- Printing tree preorder ------------" << std::endl;
        trie->preorder_node_list(trie->head());
    }

    if (kTestBoard) {
        std::cout << "Testing Board"  << std::endl;
        auto board = create_board();
        // tile_ROWxCOLUMN
        // b <-> a <-> t
        // should have bat, tab, at, ab
        auto tile_1x1 = create_letter_node('b');
        tile_1x1->set_name("1x1");
        auto tile_1x2 = create_letter_node('a');
        tile_1x2->set_name("1x2");
        auto tile_1x3 = create_letter_node('t');
        tile_1x3->set_name("1x3");

        tile_1x1->add_edge(tile_1x2);
        tile_1x2->add_edge(tile_1x1);
        tile_1x2->add_edge(tile_1x3);
        tile_1x3->add_edge(tile_1x2);

        board->add_tile(tile_1x1);
        board->add_tile(tile_1x2);
        board->add_tile(tile_1x3);

        if (board->contains_word("bat")) {
            std::cout << "bat in board as expected" << std::endl;
        } else {
            std::cout << "bat was not in board" << std::endl;
        }

        if (board->contains_word("tab")) {
            std::cout << "tab in board as expected" << std::endl;
        } else {
            std::cout << "tab was not in board" << std::endl;
        }

        if (board->contains_word("ab")) {
            std::cout << "ab in board as expected" << std::endl;
        } else {
            std::cout << "ab was not in board" << std::endl;
        }

        if (board->contains_word("a")) {
            std::cout << "a in board as expected" << std::endl;
        } else {
            std::cout << "a was not in board" << std::endl;
        }

        if (board->contains_word("taba")) {
            std::cout << "taba in board (fail)" << std::endl;
        } else {
            std::cout << "taba was not in board as expected" << std::endl;
        }

        if (board->contains_word("tac")) {
            std::cout << "tac in board (fail)" << std::endl;
        } else {
            std::cout << "tac was not in board as expected" << std::endl;
        }
    }

    if (kTestTrieFiller) {
        auto trie = create_trie();
        std::cout << "Filling trie..." << std::endl;
        fill_trie(trie);
        std::cout << "Done filling trie" << std::endl;

        if (trie->contains_word("zipper")) {
            std::cout << "zipper in trie as expected" << std::endl;
        } else {
            std::cout << "zipper not in trie (fail)" << std::endl;
        }
        if (trie->contains_word("Zipper")) {
            std::cout << "Zipper in trie!!! (fail)"  << std::endl;
        }
    }

    if (kTestTimeIt) {
        std::cout << "Testing timeit!" << std::endl;
        auto trie = create_trie();
        timeit([&trie]{fill_trie(trie);}, "fill_trie");
    }

    if (kTestSolver) {
        std::cout << "Testing Solver: creating board" << std::endl;
        auto board = create_board();

        std::vector<std::shared_ptr<LetterNode>> tiles;
        for (const auto c : "stop") {
            auto tile = tiles.emplace_back(create_letter_node(c));
            board->add_tile(tile);
        }

        // connect letters to all but themselves
        for (const auto & tile : tiles) {
            for (const auto & other_tile : tiles) {
                if (tile != other_tile) {
                    tile->add_edge(other_tile);
                }
            }
        }

        std::cout << "Testing Solver: filling trie" << std::endl;
        auto trie = create_trie();
        trie->add_word("stop");
        trie->add_word("stops");  // can only be done with cycles
        trie->add_word("post");
        trie->add_word("pots");


        std::cout << "Testing Solver: making solver" << std::endl;
        auto solver_with_cycles = create_solver(board, trie, true);
        auto solver_without_cycles = create_solver(board, trie, false);

        const auto cycle_words = solver_with_cycles->words();
        const auto no_cycle_words = solver_without_cycles->words();

        const auto contains = [] (const auto & container, const auto & item) {
            return std::find(container.begin(), container.end(), item) != container.end();
        };

        for (const auto & word : {"stop", "post", "pots", "stops"}) {
            if (!contains(cycle_words, word)) {
                std::cout << "ERROR: cycle words didn't contain: " << word << std::endl;
            }
        }

        for (const auto & word : {"stop", "post", "pots"}) {
            if (!contains(no_cycle_words, word)) {
                std::cout << "ERROR: no_cycle words didn't contain: " << word << std::endl;
            }
        }

        if (contains(no_cycle_words, "stops")) {
            std::cout << "ERROR: no_cycle words had: stops" << std::endl;
        }
    }
}

void print_help_text(std::string_view error = "") {
    std::cout << std::endl;

    if (!error.empty()) {
        std::cout << error << std::endl;
    }
    std::cout << "try one of these options:" << std::endl;
    std::cout << "1) ./run.o --test" << std::endl;
    std::cout << "2) ./run.o --spelling-bee "
              << "<CenterLetter><letter><letter><letter><letter><letter><letter>"
              << std::endl;
    std::cout << "3) ./run.o --boggle <first_row> <second_row> <...> <nth_row>" << std::endl;
}

void spelling_bee(const std::vector<std::string> & args) {
    auto letters = args[2];
    auto board = create_board();
    std::vector<std::shared_ptr<LetterNode>> nodes;
    std::cout << "Making Game Board..." << std::endl;
    timeit(
        [&nodes, &letters, &board] {
            for (const auto letter : letters) {
                auto & node = nodes.emplace_back(create_letter_node(letter));
                board->add_tile(node);
            }

            for (const auto & node_1 : nodes) {
                for (const auto & node_2 : nodes) {
                    node_1->add_edge(node_2);
                }
            }
        },
        "Making Game Board"
    );

    std::cout << "Making Dictionary..." << std::endl;
    auto trie = create_trie();
    timeit(
        [&trie, &board] {
            fill_trie(trie, board);
        },
        "Making Dictionary"
    );


    std::cout << "Solving Puzzle..." << std::endl;
    std::shared_ptr<Solver> solver;
    timeit(
        [&solver, &trie, &board] {
            solver = create_solver(board, trie, true);
        },
        "Solving Puzzle"
    );

    std::cout << "Hit Enter to print out words\n" << std::endl;
    std::cin.ignore();
    constexpr auto kMinLength = 4;
    constexpr auto kCenterLetterIndex = 0;
    for (const auto & word : solver->words()) {
        if (word.size() >= kMinLength && word.find(letters[kCenterLetterIndex]) != std::string::npos) {
            std::cout << word << std::endl;
        }
    }
}

void boggle(const std::vector<std::string> & args) {
    const auto & first_row = args[2];
    const auto number_of_rows = args.size() - 2;
    const auto number_of_columns = first_row.length();

    std::cout << "Based on the length of the first row, assuming "
              << number_of_rows << " rows and "
              << number_of_columns << " columns." << std::endl;

    auto board = create_board();

    // Step 1: transform list of strings into list of list of letternodes and add to board
    // consider using std::transform here?
    // or maybe new <ranges> header
    std::vector<std::vector<std::shared_ptr<LetterNode>>> rows;
    for (auto row_index = 2; row_index < args.size(); ++row_index) {
        const auto & row_string = args[row_index];

        if (row_string.length() != number_of_columns) {
            std::cout << "ERROR: row: [" << row_string
                      << "] did not have " << number_of_columns
                      << " columns." << std::endl;
            return;
        }

        auto & row = rows.emplace_back(std::vector<std::shared_ptr<LetterNode>>());
        for (const auto letter : row_string) {
            auto & node = row.emplace_back(create_letter_node(letter));
            board->add_tile(node);
        }
    }

    // Step 2: connect adjacent tiles
    const auto are_valid_indices = [number_of_rows,
                                    number_of_columns] (const auto row_index,
                                                        const auto column_index) {
        const auto row_in_bounds = row_index >= 0
                                   && row_index < number_of_rows;
        const auto column_in_bounds = column_index >= 0
                                      && column_index < number_of_columns;

        return row_in_bounds && column_in_bounds;
    };

    for (auto row_index = 0; row_index < number_of_rows; ++row_index) {
        for (auto column_index = 0; column_index < number_of_columns; ++column_index) {
            std::vector<std::pair<int, int>> potential_adjacent_indices = {
                {row_index - 1, column_index - 1},
                {row_index - 1, column_index},
                {row_index - 1, column_index + 1},
                {row_index, column_index - 1},
                {row_index, column_index + 1},
                {row_index + 1, column_index - 1},
                {row_index + 1, column_index},
                {row_index + 1, column_index + 1},
            };

            for (const auto & [adjacent_row_index, adjacent_column_index] : potential_adjacent_indices) {
                if (are_valid_indices(adjacent_row_index, adjacent_column_index)) {
                    rows[row_index][column_index]->add_edge(rows[adjacent_row_index][adjacent_column_index]);
                }
            }
        }
    }

    std::cout << "Making Dictionary..." << std::endl;
    auto trie = create_trie();
    timeit(
        [&trie, &board] {
            fill_trie(trie, board);
        },
        "Making Dictionary"
    );

    std::cout << "Solving Puzzle..." << std::endl;
    std::shared_ptr<Solver> solver;
    timeit(
        [&solver, &trie, &board] {
            solver = create_solver(board, trie, false);
        },
        "Solving Puzzle"
    );

    std::cout << "Hit Enter to print out words\n" << std::endl;
    std::cin.ignore();
    constexpr auto kMinLength = 3;
    constexpr auto kCenterLetterIndex = 0;
    for (const auto & word : solver->words()) {
        if (word.size() >= kMinLength) {
            std::cout << word << std::endl;
        }
    }
}

int main(int argc, char ** argv) {
    // not needed but I don't want to work with char ** :)
    std::vector<std::string> args;
    for (auto i = 0; i < argc; ++i) {
        args.push_back(std::string(argv[i]));
    }

    const auto received_params = args.size();

    constexpr auto kModeIndex = 1;

    const auto & mode = args[kModeIndex];
    if (mode == "--test") {
        manual_test();
    } else if (mode == "--spelling-bee") {
        spelling_bee(args);
    } else if (mode == "--boggle") {
        boggle(args);
    } else {
        print_help_text();
    }

    return 0;

    return EXIT_SUCCESS;
}
