#include <iostream>
#include "LetterNode/factory.hpp"


int main()
{
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

    return EXIT_SUCCESS;
}