#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "source/utils/collection.h"
#include "wifi_hal.h"
#include "source/core/wifi_8021x.h"
#include "source/utils/wifi_util.h"

extern "C" {
    void process_eap_data(wifi_8021x_data_t *data, wifi_8021x_t *module, bool new_event);
}

TEST(Wifi8021x, EapSuccess)
{
    wifi_8021x_data_t *data = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));
    wifi_8021x_data_t *prevdata = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));

    wifi_eap_frame_t *framedata = (wifi_eap_frame_t *) malloc(sizeof(wifi_eap_frame_t));
    wifi_eap_frame_t *prevframedata = (wifi_eap_frame_t *) malloc(sizeof(wifi_eap_frame_t));

    mac_addr_str_t mac_str = {0};
    char *key;

    framedata->code = wifi_eap_code_success;
    framedata->id = 42;

    data->packet_time.tv_sec = 0;
    data->data = framedata;
    data->vap = 0;

    prevframedata->code = wifi_eap_code_success;
    prevframedata->id = 40;

    prevdata->packet_time.tv_sec = 0;
    prevdata->data = prevframedata;
    prevdata->vap = 0;

    wifi_8021x_t *module = new wifi_8021x_t;
    module->bssid[0].eap_timeout = 0;
    module->bssid[0].eap_success = 0;
    module->bssid[0].eap_failure = 0;
    module->bssid[0].sta_map = hash_map_create();
    key = to_mac_str(data->mac, mac_str);
    hash_map_put(module->bssid[0].sta_map, strdup(key), prevdata);

    process_eap_data(data, module, true);

    ASSERT_EQ(module->bssid[0].eap_timeout, 0);
    ASSERT_EQ(module->bssid[0].eap_success, 1);
    ASSERT_EQ(module->bssid[0].eap_failure, 0);

}

/*
    This test is disabled currently and will fail if enabled; process_eap_data does not handle
    eap_code_failure correctly.
*/
TEST(Wifi8021x, DISABLED_EapFailure)
{
    wifi_8021x_data_t *data = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));
    wifi_8021x_data_t *prevdata = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));

    wifi_eap_frame_t *framedata = (wifi_eap_frame_t *) malloc(sizeof(wifi_eap_frame_t));
    wifi_eap_frame_t *prevframedata = (wifi_eap_frame_t *) malloc(sizeof(wifi_eap_frame_t));

    mac_addr_str_t mac_str = {0};
    char *key;

    framedata->code = wifi_eap_code_failure;
    framedata->id = 42;

    data->packet_time.tv_sec = 0;
    data->data = framedata;
    data->vap = 0;

    prevframedata->code = wifi_eap_code_failure;
    prevframedata->id = 40;

    prevdata->packet_time.tv_sec = 0;
    prevdata->data = prevframedata;
    prevdata->vap = 0;

    wifi_8021x_t *module = new wifi_8021x_t;
    module->bssid[0].eap_timeout = 0;
    module->bssid[0].eap_success = 0;
    module->bssid[0].eap_failure = 0;
    module->bssid[0].sta_map = hash_map_create();
    key = to_mac_str(data->mac, mac_str);
    hash_map_put(module->bssid[0].sta_map, strdup(key), prevdata);

    process_eap_data(data, module, true);

    ASSERT_EQ(module->bssid[0].eap_timeout, 0);
    ASSERT_EQ(module->bssid[0].eap_success, 0);
    ASSERT_EQ(module->bssid[0].eap_failure, 1);
}

TEST(Wifi8021x, HandleNullFrameData)
{
    wifi_8021x_data_t *data = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));
    int *someint = (int *) malloc(sizeof(int));
    *someint = 2;
    mac_addr_str_t mac_str = {0};
    char *key;

    data->packet_time.tv_sec = 0;
    data->data = NULL;
    data->vap = 0;

    wifi_8021x_t *module = new wifi_8021x_t;

    // should not segfault
    ASSERT_EXIT((process_eap_data(
        data,
        module,
        false), exit(0)), ::testing::ExitedWithCode(0), ".*");

    delete module;
}

TEST(Wifi8021x, HandleNullData)
{
    wifi_8021x_t *module = new wifi_8021x_t;

    // should not segfault
    ASSERT_EXIT((process_eap_data(
        NULL,
        module,
        false), exit(0)), ::testing::ExitedWithCode(0), ".*");

    delete module;
}


TEST(Wifi8021x, HandleNullModule)
{
    wifi_8021x_data_t *data = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));
    wifi_eap_frame_t *framedata = (wifi_eap_frame_t *) malloc(sizeof(wifi_eap_frame_t));

    framedata->code = 1;
    data->packet_time.tv_sec = 0;
    data->data = framedata;
    data->vap = 0;

    ASSERT_EXIT((process_eap_data(
        data,
        NULL,
        false), exit(0)), ::testing::ExitedWithCode(0), ".*");

}
