#include <gtest/gtest.h>
#include "wifi_hal.h"
#include "wifi_ctrl.h"
#include "wifi_mgr.h"
#include "wifi_util.h"

extern "C" {
    void bus_get_vap_init_parameter(const char *name, unsigned int *ret_val);
    void wifidb_init(wifi_db_t *db);

    bus_error_t mock_bus_data_get_fn(bus_handle_t *handle, char const *name, raw_data_t *data){
        data->data_type = bus_data_type_uint32;
        data->raw_data.u32 = 255;
        return bus_error_success;
    }
}

TEST(WifiCtrl, BusGetVapInitNullName)
{
    unsigned int ret_val;
    ASSERT_EXIT((bus_get_vap_init_parameter(
        NULL,
        &ret_val), exit(0)), ::testing::ExitedWithCode(0), ".*");
}

TEST(WifiCtrl, BusGetVapInit)
{
    // mock out test data
    wifidb_init(get_wifidb_obj());
    wifi_bus_desc_t *bus_desc = get_bus_descriptor();
    bus_desc->bus_data_get_fn = mock_bus_data_get_fn;
    start_wifidb();
    init_wifidb_tables();
    wifi_global_param_t global_param = { 0 };
    ((wifi_mgr_t *)get_wifimgr_obj())->hal_cap.wifi_prop.colocated_mode = 1;
    unsigned int ret_val;

    bus_get_vap_init_parameter(
        WIFI_DEVICE_MODE,
        &ret_val);

    wifi_ctrl_t *ctrl = (wifi_ctrl_t *)get_wifictrl_obj();

    ASSERT_EQ(ctrl->network_mode, 255);
    ASSERT_EQ(ret_val, 255);
}
