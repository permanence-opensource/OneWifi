/************************************************************************************
  If not stated otherwise in this file or this component's LICENSE file the
  following copyright and licenses apply:

  Copyright 2025 RDK Management

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 **************************************************************************/
#include <gtest/gtest.h>
#include "wifi_webconfig.h"
#include "source/core/wifi_ctrl.h"
#include "source/core/wifi_mgr.h"


extern "C" {
    int webconfig_vif_neighbors_apply(wifi_ctrl_t *ctrl, webconfig_subdoc_decoded_data_t *data);
    // note: the ctrl argument is not used in this function
}

// test covering NULL argument case from RDKBWIFI-201
TEST(WifiCtrlWebconfig, VifNeighborsApplyNullArguments)
{
    ASSERT_EXIT((webconfig_vif_neighbors_apply(NULL, NULL), exit(0)), ::testing::ExitedWithCode(0), ".*");
    // expected that RETURN_ERR is -1, but use the macro if possible
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

    hash_map_destroy(mgr->vif_neighbors_map);
    mgr->vif_neighbors_map = NULL;
}

/**
    data.vif_neighbors_map is destroyed by webconfig_vif_neighbors_apply, but the
    pointer is not set to NULL -- which is dangerous! this test should replace the
    above test when this issue is fixed
**/
TEST(WifiCtrlWebconfig, DISABLED_VifNeighborsApplyHappyPathCheckDestroyedMapPtr)
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

// test covering NULL argument case from RDKBWIFI-200
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

// test covering NULL argument case from RDKBWIFI-199
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

// test covering NULL argument case from RDKBWIFI-198
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

/** testcase for webconfig_vif_neighbors_apply: TEST(WifiCtrlWebconfig, VifNeighborsApplyDeleteNeighbors)
	 objective: Test that neighbors present in mgr->vif_neighbors_map but not in data->vif_neighbors_map are removed and freed.
	 expected outcome: The neighbor that existed only in mgr_map should be removed and memory freed (if possible to monitor). Function returns RETURN_OK.
**/
TEST(WifiCtrlWebconfig, VifNeighborsApplyDeleteNeighbors)
{
    // Setup manager and decoded data hash maps
    wifi_mgr_t *mgr = get_wifimgr_obj();
    hash_map_t *mgr_map = hash_map_create();
    hash_map_t *dec_map = hash_map_create();

    // Create a neighbor only in mgr_map
    vif_neighbors_t *mgr_neighbor = (vif_neighbors_t *)malloc(sizeof(vif_neighbors_t));
    ASSERT_NE(mgr_neighbor, nullptr);
    memset(mgr_neighbor, 0, sizeof(vif_neighbors_t));
    snprintf(mgr_neighbor->neighbor_id, sizeof(mgr_neighbor->neighbor_id), "unique_neighbor_1");
    // Fill other fields as needed
    hash_map_put(mgr_map, strdup(mgr_neighbor->neighbor_id), mgr_neighbor);

    // Assign hash maps to manager and decoded data
    mgr->vif_neighbors_map = mgr_map;

    webconfig_subdoc_decoded_data_t data = {0};
    data.vif_neighbors_map = dec_map;

    // Apply and remove neighbors
    ASSERT_EQ(webconfig_vif_neighbors_apply(NULL, &data), RETURN_OK);

    // After apply, neighbor should be removed from mgr_map
    void *found = hash_map_remove(mgr_map, "unique_neighbor_1");
    ASSERT_EQ(found, nullptr);

    // Cleanup maps (mgr_vif_neighbors_map is empty, dec_vif_neighbors_map is destroyed by apply)
    hash_map_destroy(mgr_map);
    mgr->vif_neighbors_map = NULL;
    // dec_map is destroyed by apply, do not destroy again
}
