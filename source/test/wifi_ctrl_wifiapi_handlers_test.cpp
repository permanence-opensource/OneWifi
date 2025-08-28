#include <gtest/gtest.h>
#include "wifi_hal.h"
#include "wifi_ctrl.h"
#include "wifi_mgr.h"
#include "wifi_util.h"

extern "C" {
    void wifiapi_handle_get_ApAssocDeviceDiagnosticResult(char **args, unsigned int num_args,
                                                                 char *result_buf, int result_buf_size);
}

TEST(WifiApi, DevArrayEarlyFree)
{
    char result_buf[1024];
    char *args[1];
    args[0] = (char *) malloc(5);
    strncpy(args[0], "1", 5);
    ASSERT_EXIT((wifiapi_handle_get_ApAssocDeviceDiagnosticResult(
        args,
        1,
        result_buf,
        1024), exit(0)), ::testing::ExitedWithCode(0), ".*");
}
