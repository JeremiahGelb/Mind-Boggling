#include <iostream>
#include "BoardLetter/BoardLetter.hpp"
#include <memory>

int main()
{
    auto h = std::make_shared<BoardLetter>('h');
    auto i = std::make_shared<BoardLetter>('i');

    h->add_edge(i);
    i->add_edge(h);

    std::cout << "---------------" << std::endl;
    std::cout << *h;
    std::cout << "---------------" << std::endl;
    std::cout << *i;
    std::cout << "---------------" << std::endl;

    return EXIT_SUCCESS;
}