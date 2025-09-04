/************************************************************************************
  If not stated otherwise in this file or this component's LICENSE file the
  following copyright and licenses apply:

  Copyright 2018 RDK Management

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

#include <stdio.h>
#include <stdbool.h>
#include "stdlib.h"
#include <pthread.h>
#include <ev.h>
#include <sys/time.h>
#include <assert.h>
#include "wifi_data_plane.h"
#include "wifi_monitor.h"
#include "wifi_db.h"
#include "wifi_mgr.h"
#include "wifi_stubs.h"
#include "wifi_ctrl.h"
#include <stdlib.h>
#include "wifi_util.h"
#ifdef __GLIBC__
#include <execinfo.h>
#endif
#include "util.h"
#include "misc.h"

wifi_mgr_t g_wifi_mgr;
wifi_misc_t g_misc;

wifi_misc_t *get_wifimisc_obj(void)
{
    return &g_misc;
}

wifi_misc_desc_t *get_misc_descriptor(void)
{
    return &g_misc.desc;
}

wifi_ccsp_t *get_wificcsp_obj(void)
{
    return &g_wifi_mgr.wifi_ccsp;
}

wifi_dml_t *get_wifidml_obj(void)
{
    return &g_wifi_mgr.wifidml;
}

wifi_db_t *get_wifidb_obj(void)
{
    return &g_wifi_mgr.wifidb;
}

wifi_ctrl_t *get_wifictrl_obj(void)
{
    return &g_wifi_mgr.ctrl;
}

wifi_mgr_t *get_wifimgr_obj(void)
{
    return &g_wifi_mgr;
}

webconfig_t *get_webconfig_obj(void)
{
    return &g_wifi_mgr.ctrl.webconfig;
}

bool is_db_consolidated()
{
    return g_wifi_mgr.ctrl.db_consolidated;
}

bool is_db_backup_required()
{
    return (g_wifi_mgr.ctrl.dev_type != dev_subtype_pod);
}

bool is_devtype_pod()
{
    return (g_wifi_mgr.ctrl.dev_type == dev_subtype_pod);
}
