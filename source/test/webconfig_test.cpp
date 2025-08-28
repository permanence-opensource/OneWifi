#include <gtest/gtest.h>
#include "wifi_webconfig.h"
#include "source/core/wifi_ctrl.h"

extern "C" {
    int webconfig_vif_neighbors_apply(wifi_ctrl_t *ctrl, webconfig_subdoc_decoded_data_t *data);
}

TEST(WebConfig, NullDeref)
{
    ASSERT_EXIT((webconfig_vif_neighbors_apply(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
}
