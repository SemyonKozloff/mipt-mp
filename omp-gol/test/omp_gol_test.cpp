#include <vector>

#include <gtest/gtest.h>
#include <omp.h>

#include "omp_gol.h"

TEST(omp_gol_test, correctness)
{
    const std::size_t NUM_THREADS = 4;
    omp_set_num_threads(NUM_THREADS);

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

    omp_game_of_life game(init_generation);
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

    game = std::move(omp_game_of_life(init_generation));
    game.launch(NUM_STEPS);

    EXPECT_EQ(final_generation, game.get_current_generation());
    EXPECT_EQ(NUM_STEPS, game.get_num_generations());
}

TEST(omp_gol_test, performance)
{
    const std::size_t X_SIZE = 1000;
    const std::size_t Y_SIZE = 1000;
    const std::size_t NUM_STEPS = 100;
    const std::size_t NUM_THREADS = 4;

    auto random_generation = omp_game_of_life::get_random_generation(X_SIZE, Y_SIZE);

    // single-thread test
    omp_game_of_life single_thread_game(random_generation);

    omp_set_num_threads(1);
    double start_time = omp_get_wtime();
    single_thread_game.launch(NUM_STEPS);
    double finish_time = omp_get_wtime();
    double st_time = finish_time - start_time;
    auto st_final_generation = single_thread_game.get_current_generation();

    // multi-thread test
    omp_game_of_life multi_thread_game(random_generation);

    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    multi_thread_game.launch(NUM_STEPS);
    finish_time = omp_get_wtime();
    double mt_time = finish_time - start_time;
    auto mt_final_generation = multi_thread_game.get_current_generation();

    ASSERT_EQ(st_final_generation, mt_final_generation);
    EXPECT_LE(mt_time, st_time);
    std::cout << st_time << ' ' << mt_time << std::endl;
}
