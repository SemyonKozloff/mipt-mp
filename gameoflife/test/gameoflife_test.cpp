#include <vector>

#include <gtest/gtest.h>

#include "gameoflife.h"
#include "utils.h"

TEST(gameoflife_test, correctness)
{
    // test 1
    std::vector<std::vector<char>> input =
            {{0, 0, 1, 0, 0, 0},
             {0, 0, 0, 1, 0, 0},
             {0, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    std::vector<std::vector<char>> expected =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 1, 1},
             {0, 0, 0, 0, 1, 1}};

    gameoflife game(input);
    game.launch();

    auto result = game.get_current_generation();

    EXPECT_EQ(expected, result);

    // test 2
    const std::size_t num_steps = 7;

    input =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 1, 0, 0, 0},
             {0, 0, 1, 0, 0, 0},
             {0, 0, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    expected =
            {{0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0}};

    game = gameoflife(input);
    game.launch(num_steps);
    result = game.get_current_generation();

    EXPECT_EQ(expected, result);
    EXPECT_EQ(num_steps, game.get_num_generations());
}
