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
    constexpr auto kTestTrieFiller = true;
    constexpr auto kTestTimeIt = true;
    constexpr auto kTestSolver = false;

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
        // spelling bee
        //  p a g o d y center=e
        auto tile_1 = create_letter_node('p');
        auto tile_2 = create_letter_node('a');
        auto tile_3 = create_letter_node('g');
        auto tile_4 = create_letter_node('o');
        auto tile_5 = create_letter_node('d');
        auto tile_6 = create_letter_node('y');
        auto tile_7 = create_letter_node('e');
        tile_1->set_name("1");
        tile_2->set_name("2");
        tile_3->set_name("3");
        tile_4->set_name("4");
        tile_5->set_name("5");
        tile_6->set_name("6");
        tile_7->set_name("7");


        tile_1->add_edge(tile_1);
        tile_1->add_edge(tile_2);
        tile_1->add_edge(tile_3);
        tile_1->add_edge(tile_4);
        tile_1->add_edge(tile_5);
        tile_1->add_edge(tile_6);
        tile_1->add_edge(tile_7);

        tile_2->add_edge(tile_1);
        tile_2->add_edge(tile_2);
        tile_2->add_edge(tile_3);
        tile_2->add_edge(tile_4);
        tile_2->add_edge(tile_5);
        tile_2->add_edge(tile_6);
        tile_2->add_edge(tile_7);

        tile_3->add_edge(tile_1);
        tile_3->add_edge(tile_2);
        tile_3->add_edge(tile_3);
        tile_3->add_edge(tile_4);
        tile_3->add_edge(tile_5);
        tile_3->add_edge(tile_6);
        tile_3->add_edge(tile_7);

        tile_4->add_edge(tile_1);
        tile_4->add_edge(tile_2);
        tile_4->add_edge(tile_3);
        tile_4->add_edge(tile_4);
        tile_4->add_edge(tile_5);
        tile_4->add_edge(tile_6);
        tile_4->add_edge(tile_7);

        tile_5->add_edge(tile_1);
        tile_5->add_edge(tile_2);
        tile_5->add_edge(tile_3);
        tile_5->add_edge(tile_4);
        tile_5->add_edge(tile_5);
        tile_5->add_edge(tile_6);
        tile_5->add_edge(tile_7);

        tile_6->add_edge(tile_1);
        tile_6->add_edge(tile_2);
        tile_6->add_edge(tile_3);
        tile_6->add_edge(tile_4);
        tile_6->add_edge(tile_5);
        tile_6->add_edge(tile_6);
        tile_6->add_edge(tile_7);

        tile_7->add_edge(tile_1);
        tile_7->add_edge(tile_2);
        tile_7->add_edge(tile_3);
        tile_7->add_edge(tile_4);
        tile_7->add_edge(tile_5);
        tile_7->add_edge(tile_6);
        tile_7->add_edge(tile_7);

        board->add_tile(tile_1);
        board->add_tile(tile_2);
        board->add_tile(tile_3);
        board->add_tile(tile_4);
        board->add_tile(tile_5);
        board->add_tile(tile_6);
        board->add_tile(tile_7);

        std::cout << "Testing Solver: filling trie" << std::endl;
        auto trie = create_trie();
        fill_trie(trie, board);


        std::cout << "Testing Solver: making solver" << std::endl;
        auto solver = create_solver(board, trie);

        constexpr auto kMinLength = 4;
        for (const auto & word : solver->words()) {
            if (word.size() >= kMinLength && word.find('e') != std::string::npos) {
                // std::cout << word << std::endl;
            }
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
    std::cout << "2) ./run.o --spellingbee <CenterLetter><letter><letter><letter><letter><letter><letter>" << std::endl;
}

void spelling_bee(const std::vector<std::string> & args) {
    auto letters = args[2];
    auto board = create_board();
    std::vector<std::shared_ptr<LetterNode>> nodes;
    std::cout << "Making Game Board..." << std::endl;
    timeit(
        [&nodes, &letters, &board] {
            for (const auto letter : letters) {
                auto node = nodes.emplace_back(create_letter_node(letter));
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
            solver = create_solver(board, trie);
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
    } else if (mode == "--spellingbee") {
        spelling_bee(args);
    } else {
        print_help_text();
    }

    return 0;

    return EXIT_SUCCESS;
}
