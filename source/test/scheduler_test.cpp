#include <gtest/gtest.h>

#include "source/utils/scheduler.h"

TEST(Scheduler, HappyPath)
{
    struct scheduler *the_obj = scheduler_init();
    EXPECT_NE(the_obj, nullptr);

    int return_val = scheduler_deinit(&the_obj);
    EXPECT_EQ(return_val, 0);
    EXPECT_EQ(the_obj, nullptr);
}

TEST(Scheduler, NullDeref)
{
    // int return_val = ;
    ASSERT_EXIT((scheduler_deinit(NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
}
