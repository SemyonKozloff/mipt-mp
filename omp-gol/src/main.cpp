#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    //game_of_life(game_of_life::get_random_generation(100, 100)).launch(10);

}