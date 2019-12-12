#include "factory.hpp"

std::shared_ptr<Board> create_board() {
    return std::make_shared<Board>();
}
