#include <vector>

#include <gtest/gtest.h>
#include <omp.h>

#include "omp_gameoflife.h"

TEST(omp_gameoflife, correctness)
{
    const std::size_t num_threads = 4;
    omp_set_num_threads(num_threads);

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

    omp_gameoflife game(input);
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

    game = omp_gameoflife(input);
    game.launch(num_steps);
    result = game.get_current_generation();

    EXPECT_EQ(expected, result);
    EXPECT_EQ(num_steps, game.get_num_generations());
}

TEST(omp_gameoflife_test, performance)
{
    const std::size_t x_size = 1000;
    const std::size_t y_size = 1000;
    const std::size_t num_steps = 100;
    const std::size_t num_threads = 4;

    auto random_generation = gameoflife::get_random_generation(x_size, y_size);

    // single-thread test
    gameoflife single_thread_game(random_generation);

    double start_time = omp_get_wtime();
    single_thread_game.launch(num_steps);
    double finish_time = omp_get_wtime();
    double st_time = finish_time - start_time;
    auto st_final_generation = single_thread_game.get_current_generation();

    // multi-thread test
    omp_gameoflife multi_thread_game(random_generation);

    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();
    multi_thread_game.launch(num_steps);
    finish_time = omp_get_wtime();
    double mt_time = finish_time - start_time;
    auto mt_final_generation = multi_thread_game.get_current_generation();

    ASSERT_EQ(st_final_generation, mt_final_generation);
    EXPECT_LE(mt_time, st_time);
    std::cout << st_time << ' ' << mt_time << std::endl;
}
