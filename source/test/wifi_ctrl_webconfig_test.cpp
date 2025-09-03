#include <gtest/gtest.h>
#include "wifi_webconfig.h"
#include "source/core/wifi_ctrl.h"
#include "source/core/wifi_mgr.h"


extern "C" {
    int webconfig_vif_neighbors_apply(wifi_ctrl_t *ctrl, webconfig_subdoc_decoded_data_t *data);
    // note: the ctrl argument is not used in this function
}

TEST(WifiCtrlWebconfig, VifNeighborsApplyNullArguments)
{
    ASSERT_EXIT((webconfig_vif_neighbors_apply(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
    // expected that RETURN_ERR is -1, butuse the macro if possible
    ASSERT_EQ(webconfig_vif_neighbors_apply(NULL, NULL), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, VifNeighborsApplyNullNeighborsMap)
{
    webconfig_subdoc_decoded_data_t data = {0};
    data.vif_neighbors_map = NULL;
    ASSERT_EXIT((webconfig_vif_neighbors_apply(NULL, &data), exit(0)), ::testing::ExitedWithCode(0), ".*");

    // expected that RETURN_ERR is -1, butuse the macro if possible
    ASSERT_EQ(webconfig_vif_neighbors_apply(NULL, &data), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, VifNeighborsApplyHappyPathEmptyHashMap)
{
    webconfig_subdoc_decoded_data_t data = {0};
    data.vif_neighbors_map = hash_map_create();

    wifi_mgr_t *mgr = get_wifimgr_obj();
    mgr->vif_neighbors_map = hash_map_create();

    ASSERT_EQ(webconfig_vif_neighbors_apply(NULL, &data), RETURN_OK);

    // this should really be null, since it's been destroyed!
    // use below test to check
    //ASSERT_EQ(data.vif_neighbors_map, nullptr);

    hash_map_destroy(mgr->vif_neighbors_map);
    mgr->vif_neighbors_map = NULL;
}

TEST(WifiCtrlWebconfig, VifNeighborsApplyHappyPathCheckDestroyedMapPtr)
{
    webconfig_subdoc_decoded_data_t data = {0};
    data.vif_neighbors_map = hash_map_create();

    wifi_mgr_t *mgr = get_wifimgr_obj();
    mgr->vif_neighbors_map = hash_map_create();

    ASSERT_EQ(webconfig_vif_neighbors_apply(NULL, &data), RETURN_OK);

    // this should really be null, since it's been destroyed!
    ASSERT_EQ(data.vif_neighbors_map, nullptr);

    hash_map_destroy(mgr->vif_neighbors_map);
    mgr->vif_neighbors_map = NULL;
}

extern "C" {
    int webconfig_steering_config_apply(wifi_ctrl_t *ctrl, webconfig_subdoc_decoded_data_t *data);
}

TEST(WifiCtrlWebconfig, SteeringConfigApplyNullArguments)
{
    ASSERT_EXIT((webconfig_steering_config_apply(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
    // expected that RETURN_ERR is -1, butuse the macro if possible
    ASSERT_EQ(webconfig_steering_config_apply(NULL, NULL), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, SteeringConfigApplyNullNeighborsMap)
{
    // expected that RETURN_ERR is -1, butuse the macro if possible
    webconfig_subdoc_decoded_data_t data = {0};
    data.steering_config_map = NULL;

    ASSERT_EQ(webconfig_steering_config_apply(NULL, &data), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, SteeringConfigApplySameNeighborsMap)
{
    wifi_mgr_t *mgr = get_wifimgr_obj();

    webconfig_subdoc_decoded_data_t data = {0};
    data.steering_config_map = hash_map_create();
    mgr->steering_config_map = data.steering_config_map;

    ASSERT_EQ(webconfig_steering_config_apply(NULL, &data), RETURN_OK);

    mgr->steering_config_map = NULL;
}

TEST(WifiCtrlWebconfig, SteeringConfigApplyEmptyNeighborsMap)
{
    wifi_mgr_t *mgr = get_wifimgr_obj();

    webconfig_subdoc_decoded_data_t data = {0};
    data.steering_config_map = hash_map_create();
    mgr->steering_config_map = hash_map_create();

    ASSERT_EQ(webconfig_steering_config_apply(NULL, &data), RETURN_OK);

    hash_map_destroy(mgr->steering_config_map);
    mgr->steering_config_map = NULL;
}

extern "C" {
    int webconfig_steering_clients_apply(wifi_ctrl_t *ctrl, webconfig_subdoc_decoded_data_t *data);
}

TEST(WifiCtrlWebconfig, SteeringClientsApplyNullArguments)
{
    ASSERT_EXIT((webconfig_steering_clients_apply(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
    // expected that RETURN_ERR is -1, butuse the macro if possible
    ASSERT_EQ(webconfig_steering_clients_apply(NULL, NULL), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, SteeringClientsApplyNullClientMap)
{
    // expected that RETURN_ERR is -1, butuse the macro if possible
    webconfig_subdoc_decoded_data_t data = {0};
    data.steering_client_map = NULL;

    ASSERT_EQ(webconfig_steering_clients_apply(NULL, &data), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, SteeringClientsApplyEmptyClientMap)
{
    wifi_mgr_t *mgr = get_wifimgr_obj();

    webconfig_subdoc_decoded_data_t data = {0};
    data.steering_client_map = hash_map_create();
    mgr->steering_client_map = data.steering_client_map;

    ASSERT_EQ(webconfig_steering_clients_apply(NULL, &data), RETURN_OK);

    mgr->steering_client_map = NULL;
}

TEST(WifiCtrlWebconfig, SteeringClientsSameClientMap)
{
    wifi_mgr_t *mgr = get_wifimgr_obj();

    webconfig_subdoc_decoded_data_t data = {0};
    data.steering_client_map = hash_map_create();
    mgr->steering_client_map = hash_map_create();

    ASSERT_EQ(webconfig_steering_clients_apply(NULL, &data), RETURN_OK);

    hash_map_destroy(mgr->steering_client_map);
    mgr->steering_client_map = NULL;
}

extern "C" {
    int webconfig_stats_config_apply(wifi_ctrl_t *ctrl, webconfig_subdoc_decoded_data_t *data);
}

TEST(WifiCtrlWebconfig, StatsConfigApplyNullArguments)
{
    ASSERT_EXIT((webconfig_stats_config_apply(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
    // expected that RETURN_ERR is -1, butuse the macro if possible
    ASSERT_EQ(webconfig_stats_config_apply(NULL, NULL), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, StatsConfigsApplyNullStatsConfigMap)
{
    // expected that RETURN_ERR is -1, butuse the macro if possible
    webconfig_subdoc_decoded_data_t data = {0};
    data.stats_config_map = NULL;

    ASSERT_EQ(webconfig_stats_config_apply(NULL, &data), RETURN_ERR);
}

TEST(WifiCtrlWebconfig, StatsConfigApplyEmptyStatsConfigMap)
{
    wifi_mgr_t *mgr = get_wifimgr_obj();

    webconfig_subdoc_decoded_data_t data = {0};
    data.stats_config_map = hash_map_create();
    mgr->stats_config_map = data.stats_config_map;

    ASSERT_EQ(webconfig_stats_config_apply(NULL, &data), RETURN_OK);

    mgr->stats_config_map = NULL;
}

TEST(WifiCtrlWebconfig, StatsConfigSameStatsConfigMap)
{
    wifi_mgr_t *mgr = get_wifimgr_obj();

    webconfig_subdoc_decoded_data_t data = {0};
    data.stats_config_map = hash_map_create();
    mgr->stats_config_map = hash_map_create();

    ASSERT_EQ(webconfig_stats_config_apply(NULL, &data), RETURN_OK);

    hash_map_destroy(mgr->stats_config_map);
    mgr->stats_config_map = NULL;
}
