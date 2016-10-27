#include <iostream>

void display_grid(const auto& grid)
{
    for (auto&& row : grid)
    {
        for (auto&& cell : row)
        {
            std::cout << std::size_t(cell) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
