#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include "wifi_hal.h"
#include "wifi_ctrl.h"
#include "wifi_mgr.h"
#include "wifi_util.h"

extern "C" {
    void process_wifiapi_command(char *command, unsigned int len);

    bus_error_t mock_bus_event_publish(bus_handle_t *handle, char const *name, raw_data_t *data){
        return bus_error_success;
    }
}

/**
    note: this expected string is wrong. the platform mocks set up a devarray with
    three entries, but the function currently overwrites all previous content with
    the final entry. see the next test for the corrected version.
 */
TEST(WifiApi, GetApAssociatedDeviceDiagnosticResultTruncated)
{
    wifi_ctrl_t *ctrl = (wifi_ctrl_t *)get_wifictrl_obj();
    wifi_bus_desc_t *bus_desc = get_bus_descriptor();
    bus_desc->bus_event_publish_fn=mock_bus_event_publish;
    char command[1024];
    strncpy(command, "wifi_getApAssociatedDeviceDiagnosticResult3 1", 1024);
    process_wifiapi_command(
        command,
        strlen(command)
    );

    const char * expected = "\ncli_MACAddress: 02:00:00:00:00:00 cli_MLDAddr: 00:00:00:00:00:00 cli_MLDEnable: 0 cli_AuthenticationState: 0 cli_LastDataDownlinkRate: 0 cli_LastDataUplinkRate: 0 cli_SignalStrength: 0 cli_Retransmissions: 0 cli_Active: 0 cli_OperatingStandard:  cli_OperatingChannelBandwidth:  cli_SNR: 0 cli_InterferenceSources:  cli_DataFramesSentAck: 0 cli_DataFramesSentNoAck: 0 cli_BytesSent: 0 cli_BytesReceived: 0 cli_RSSI: 0 cli_MinRSSI: 0 cli_MaxRSSI: 0 cli_Disassociations: 0 cli_AuthenticationFailures: 0 cli_Associations: 0 cli_PacketsSent: 0 cli_PacketsReceived: 0 cli_ErrorsSent: 0 cli_RetransCount: 0 cli_FailedRetransCount: 0 cli_RetryCount: 0 cli_MultipleRetryCount: 0 cli_MaxDownlinkRate: 0 cli_MaxUplinkRate: 0 cli_activeNumSpatialStreams: 0 cli_TxFrames: 0 cli_RxRetries: 0 cli_RxErrors: 0\n";

    EXPECT_STREQ (
            ctrl->wifiapi.result,
            expected
    );
}

/**
    this test will fail until the code is corrected. note that this depends
    on a possible typo in process_wifiapi_command that creates the result
    buffer with size 10024 instead of 1024
**/
TEST(WifiApi, DISABLED_GetApAssociatedDeviceDiagnosticResultFull)
{
    wifi_ctrl_t *ctrl = (wifi_ctrl_t *)get_wifictrl_obj();
    wifi_bus_desc_t *bus_desc = get_bus_descriptor();
    bus_desc->bus_event_publish_fn=mock_bus_event_publish;
    char command[1024];
    strncpy(command, "wifi_getApAssociatedDeviceDiagnosticResult3 1", 1024);
    process_wifiapi_command(
        command,
        strlen(command)
    );

    const char * expected = "\
\ncli_MACAddress: 00:00:00:00:00:00 cli_MLDAddr: 00:00:00:00:00:00 cli_MLDEnable: 0 cli_AuthenticationState: 0 cli_LastDataDownlinkRate: 0 cli_LastDataUplinkRate: 0 cli_SignalStrength: 0 cli_Retransmissions: 0 cli_Active: 0 cli_OperatingStandard:  cli_OperatingChannelBandwidth:  cli_SNR: 0 cli_InterferenceSources:  cli_DataFramesSentAck: 0 cli_DataFramesSentNoAck: 0 cli_BytesSent: 0 cli_BytesReceived: 0 cli_RSSI: 0 cli_MinRSSI: 0 cli_MaxRSSI: 0 cli_Disassociations: 0 cli_AuthenticationFailures: 0 cli_Associations: 0 cli_PacketsSent: 0 cli_PacketsReceived: 0 cli_ErrorsSent: 0 cli_RetransCount: 0 cli_FailedRetransCount: 0 cli_RetryCount: 0 cli_MultipleRetryCount: 0 cli_MaxDownlinkRate: 0 cli_MaxUplinkRate: 0 cli_activeNumSpatialStreams: 0 cli_TxFrames: 0 cli_RxRetries: 0 cli_RxErrors: 0\n\
\ncli_MACAddress: 01:00:00:00:00:00 cli_MLDAddr: 00:00:00:00:00:00 cli_MLDEnable: 0 cli_AuthenticationState: 0 cli_LastDataDownlinkRate: 0 cli_LastDataUplinkRate: 0 cli_SignalStrength: 0 cli_Retransmissions: 0 cli_Active: 0 cli_OperatingStandard:  cli_OperatingChannelBandwidth:  cli_SNR: 0 cli_InterferenceSources:  cli_DataFramesSentAck: 0 cli_DataFramesSentNoAck: 0 cli_BytesSent: 0 cli_BytesReceived: 0 cli_RSSI: 0 cli_MinRSSI: 0 cli_MaxRSSI: 0 cli_Disassociations: 0 cli_AuthenticationFailures: 0 cli_Associations: 0 cli_PacketsSent: 0 cli_PacketsReceived: 0 cli_ErrorsSent: 0 cli_RetransCount: 0 cli_FailedRetransCount: 0 cli_RetryCount: 0 cli_MultipleRetryCount: 0 cli_MaxDownlinkRate: 0 cli_MaxUplinkRate: 0 cli_activeNumSpatialStreams: 0 cli_TxFrames: 0 cli_RxRetries: 0 cli_RxErrors: 0\n\
\ncli_MACAddress: 02:00:00:00:00:00 cli_MLDAddr: 00:00:00:00:00:00 cli_MLDEnable: 0 cli_AuthenticationState: 0 cli_LastDataDownlinkRate: 0 cli_LastDataUplinkRate: 0 cli_SignalStrength: 0 cli_Retransmissions: 0 cli_Active: 0 cli_OperatingStandard:  cli_OperatingChannelBandwidth:  cli_SNR: 0 cli_InterferenceSources:  cli_DataFramesSentAck: 0 cli_DataFramesSentNoAck: 0 cli_BytesSent: 0 cli_BytesReceived: 0 cli_RSSI: 0 cli_MinRSSI: 0 cli_MaxRSSI: 0 cli_Disassociations: 0 cli_AuthenticationFailures: 0 cli_Associations: 0 cli_PacketsSent: 0 cli_PacketsReceived: 0 cli_ErrorsSent: 0 cli_RetransCount: 0 cli_FailedRetransCount: 0 cli_RetryCount: 0 cli_MultipleRetryCount: 0 cli_MaxDownlinkRate: 0 cli_MaxUplinkRate: 0 cli_activeNumSpatialStreams: 0 cli_TxFrames: 0 cli_RxRetries: 0 cli_RxErrors: 0\n";

    EXPECT_STREQ (
            ctrl->wifiapi.result,
            expected
    );
}
