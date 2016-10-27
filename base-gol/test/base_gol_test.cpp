#include <vector>

#include <gtest/gtest.h>

#include "base_gol.h"

TEST(base_gol_test, correctness)
{
    // test 1
    std::vector<std::vector<char>> init_generation =
            {{0, 0, 1, 0, 0, 0},
             {0, 0, 0, 1, 0, 0},
             {0, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    std::vector<std::vector<char>> final_generation =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 1},
             {0, 0, 0, 0, 1, 1}};

    game_of_life game(init_generation);
    game.launch();

    EXPECT_EQ(final_generation, game.get_current_generation());

    // test 2
    const std::size_t NUM_STEPS = 7;

    init_generation =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 1, 0, 0, 0},
             {0, 0, 1, 0, 0, 0},
             {0, 0, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    final_generation =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    game = std::move(game_of_life(init_generation));
    game.launch(NUM_STEPS);

    EXPECT_EQ(final_generation, game.get_current_generation());
    EXPECT_EQ(NUM_STEPS, game.get_num_generations());
}