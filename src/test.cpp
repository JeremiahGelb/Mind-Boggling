#include <iostream>
#include "LetterNode/factory.hpp"
#include "Trie/factory.hpp"


int main()
{

    constexpr auto kTestLetterNode = true;
    constexpr auto kTestTrie = true;

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
        if (trie->word_in_tree("cat")) {
            std::cout << "cat was in tree!" << std::endl;
        }
    }


    return EXIT_SUCCESS;
}