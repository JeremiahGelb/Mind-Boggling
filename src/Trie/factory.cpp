#include "factory.hpp"

std::shared_ptr<Trie> create_trie()
{
    return std::make_shared<Trie>();
}
