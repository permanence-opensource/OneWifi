#include <gtest/gtest.h>
#include "source/utils/collection.h"
#include "wifi_hal.h"
#include "source/core/wifi_8021x.h"
#include "source/utils/wifi_util.h"

extern "C" {
    void process_eap_data(wifi_8021x_data_t *data, wifi_8021x_t *module, bool new_event);
}

TEST(Wifi8021x, NullDeref)
{
    wifi_8021x_data_t *data = (wifi_8021x_data_t *) malloc(sizeof(wifi_8021x_data_t));
    wifi_eap_frame_t *framedata = (wifi_eap_frame_t *) malloc(sizeof(wifi_eap_frame_t));
    int *someint = (int *) malloc(sizeof(int));
    *someint = 2;
    mac_addr_str_t mac_str = {0};
    char *key;

    framedata->code = 1;
    data->packet_time.tv_sec = 0;
    data->data = framedata;
    data->vap = 0;

    wifi_8021x_t *module = new wifi_8021x_t;
    module->bssid[0].sta_map = hash_map_create();
    key = to_mac_str(data->mac, mac_str);
    hash_map_put(module->bssid[0].sta_map, strdup(key), someint);

    ASSERT_NE(hash_map_get(module->bssid[0].sta_map, key), nullptr);

    // int return_val = ;
    process_eap_data(data, module, false);

    ASSERT_EQ(hash_map_get(module->bssid[0].sta_map, key), nullptr);

}
