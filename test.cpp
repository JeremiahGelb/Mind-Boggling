#include <iostream>
#include "BoardLetter/factory.hpp"


int main()
{
    auto h = create_board_letter('h');
    auto i = create_board_letter('i');

    h->add_edge(i);
    i->add_edge(h);

    std::cout << "---------------" << std::endl;
    std::cout << *h;
    std::cout << "---------------" << std::endl;
    std::cout << *i;
    std::cout << "---------------" << std::endl;

    return EXIT_SUCCESS;
}