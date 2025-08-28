#include <gtest/gtest.h>

#include "source/platform/linux/he_bus/inc/he_bus_data_conversion.h"

TEST(HeBus, NullDeref)
{
    // int return_val = ;
    ASSERT_EXIT((convert_buffer_to_bus_raw_msg_data(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
}
