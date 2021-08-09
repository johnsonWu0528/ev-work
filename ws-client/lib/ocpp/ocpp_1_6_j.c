#include <stdio.h>
#include <stdlib.h>
#include "../json/cJSON.h"
#include "ocpp_1_6_j.h"

/* private extern for test and implement*/

static const char t_chargeBoxSerialNumber[]   = "1";
static const char t_chargePointModel[]        = "1";
static const char t_chargePointVendor[]       = "1";
static const char t_chargePointSerialNumber[] = "1";
static const char t_firmwareVersion[]         = "1";
static const char t_iccid[]                   = "1";
static const char t_imsi[]                    = "1";
static const char t_meterSerialNumber[]       = "1";
static const char t_meterType[]               = "1";
static const char t_connectorId[]             = "1";
static const char t_type[]                    = "1";
static const char t_key[]                     = "1";
static const char t_value[]                   = "value";
static const char t_info[]                    = "1";
static const char t_vendorID[]                = "Noodoe_FW";
static const char t_vendor_error_code[]       = "no_error";
static const char t_messageID[]               = "messageID";
static const char t_data[]                    = "data";
static const char t_transactionId[]           = "transactionId";
static const char t_timestamp[]               = "timestamp";
static const char t_idTag[]                   = "idTag";
static const char t_meterStart[]              = "meterStart";
static const char t_reservationId[]           = "reservationId";
static const char t_profile_id[]              = "profile_id";
static const char t_stack_level[]              = "1";

static const ocpp_string m_core_action[OCPP_CORE_ACTION_MAX] =
{
  {"Authorize", 9},
  {"BootNotification", 16},
  {"ChangeAvailability", 18},
  {"ChangeConfiguration", 19},
  {"ClearCache", 10},
  {"DataTransfer", 12},
  {"GetConfiguration", 16},
  {"Heartbeat", 9},
  {"MeterValues", 11},
  {"RemoteStartTransaction", 22},
  {"RemoteStopTransaction", 21},
  {"Reset", 5},
  {"StartTransaction", 16},
  {"StatusNotification", 15},
  {"StopTransaction", 15},
  {"UnlockConnector", 15}
};

static const ocpp_string m_filed_req_name[OCPP_REQ_MESSAGES_MAX] =
{
  {"idTag", 5},
  {"chargeBoxSerialNumber", 21},
  {"chargePointModel", 16},
  {"chargePointSerialNumber", 23},
  {"chargePointVendor", 17},
  {"firmwareVersion", 15},
  {"iccid", 5},
  {"imsi", 4},
  {"meterSerialNumber", 17},
  {"meterType", 9},
  {"reservationId", 13},
  {"connectorId", 11},
  {"type", 4},
  {"key", 3},
  {"value", 5},
  {"id", 5},
  {"chargingProfilePurpose", 22},
  {"stackLevel", 10},
  {"vendorId", 8},
  {"messageId", 9},
  {"data", 4},
  {"status", 6},
  {"duration", 8},
  {"chargingRateUnit", 16},
  {"location", 8},
  {"retries", 7},
  {"retryInterval", 13},
  {"startTime", 9},
  {"stopTime", 8},
  {"transactionId", 13},
  {"meterValue", 10},
  {"chargingProfile", 15},
  {"expiryDate", 10},
  {"parentIdTag", 11},
  {"localAuthorizationList", 22},
  {"updateType", 10},
  {"csChargingProfiles", 18},
  {"meterStart", 10},
  {"timestamp", 9},
  {"errorCode", 9},
  {"info", 4},
  {"vendorErrorCode", 15},
  {"meterStop", 9},
  {"reason", 6},
  {"transactionData", 15},
  {"requestedMessage", 16},
  {"retrieveDate", 12},
  {"smapleValue", 10}
};

static const ocpp_string m_filed_conf_name[OCPP_CONF_MESSAGES_MAX] =
{
  {"idTagInfo", 9},
  {"currentTime", 11},
  {"interval", 5},
  {"status", 6},
  {"data", 4},
  {"connectorId", 11},
  {"scheduleStart", 13},
  {"chargingSchedule", 16},
  {"configurationKey", 16},
  {"unknownKey", 10},
  {"fileName", 8},
  {"listVersion", 11},
  {"transactionId", 13}
};

static const ocpp_string m_charge_point_error_code[OCPP_ERR_MAX] =
{
  {"ConnectorLockFailure", 20},
  {"EVCommunicationError", 20},
  {"GroundFailure", 13},
  {"HighTemperature", 15},
  {"InternalError", 13},
  {"LocalListConflict", 17},
  {"NoError", 7},
  {"OtherError", 10},
  {"OverCurrentFailure", 18},
  {"OverVoltage", 11},
  {"PowerMeterFailure", 17},
  {"PowerSwitchFailure", 18},
  {"ReaderFailure", 13},
  {"ResetFailure", 12},
  {"UnderVoltage", 12},
  {"WeakSignal", 10},
};

static const ocpp_string m_charge_point_status[OCPP_STATUS_MAX] =
{
  {"Available", 9},
  {"Preparing", 9},
  {"Charging", 8},
  {"SuspendedEVSE", 13},
  {"SuspendedEV", 11},
  {"Finishing", 9},
  {"Reserved", 8},
  {"Unavailable", 11},
  {"Faulted", 7}
};

static const ocpp_string m_clear_cachce_status[OCPP_CLEAR_CACHE_MAX] =
{
  {"Accepted", 8},
  {"Rejected", 8}
};

static const ocpp_string m_smaple_value[OCPP_SAMPLE_VALUE_MAX] =
{
  {"value", 5},
  {"context", 7},
  {"format", 6},
  {"measurand", 9},
  {"phase", 5},
  {"location", 8},
  {"unit", 4},
};

static const ocpp_string m_reading_context[OCPP_READING_CONTEXT_MAX] =
{
  {"Interruption.Begin", 18},
  {"Interruption.End", 16},
  {"Other", 5},
  {"Sample.clock", 12},
  {"Sample.Periodic", 15},
  {"Transaction.Begin", 17},
  {"Transaction.End", 15},
  {"Trigger", 7},
};

static const ocpp_string m_value_format[OCPP_VALUE_FORMAE_MAX] =
{
  {"Raw", 3},
  {"SignedData",10}
};

static const ocpp_string m_measurand[OCPP_MEASURAND_MAX] =
{
  {"Current.Export", 14},
  {"Current.Import", 14},
  {"Current.Offered", 15},
  {"Energy.Active.Export.Register", 29},
  {"Energy.Active.Import.Register", 29},
  {"Energy.Reactive.Export.Register", 31},
  {"Energy.Reactive.Import.Register", 31},
  {"Energy.Active.Export.Interval", 29},
  {"Energy.Active.Import.Interval", 29},
  {"Energy.Reactive.Export.Interval", 31},
  {"Energy.Reactive.Import.Interval", 31},
  {"Frequency", 9},
  {"Power.Active.Export", 19},
  {"Power.Active.Import", 19},
  {"Power.Factor", 12},
  {"Power.Offered", 13},
  {"Power.Reactive.Export", 21},
  {"Power.Reactive.Import", 21},
  {"RPM", 3},
  {"SoC", 3},
  {"Temperature", 11},
  {"Voltage", 7}
};

static const ocpp_string m_phase[OCPP_PHASE_MAX] =
{
  {"L1", 2},
  {"L2", 2},
  {"L3", 2},
  {"N", 1},
  {"L1-N", 4},
  {"L2-N", 4},
  {"L3-N", 4},
  {"L1-L2", 5},
  {"L2-L3", 5},
  {"L3-L1", 5}
};

static const ocpp_string m_location[OCPP_LOCATION_MAX] =
{
  {"Body", 4},
  {"Cable", 5},
  {"EV", 2},
  {"Inlet", 5},
  {"Outlet", 6},
};

static const ocpp_string m_unit_of_measure[OCPP_UNIT_OF_MEASURE_MAX] =
{
  {"Wh", 2},
  {"kWh", 3},
  {"varh", 4},
  {"kvarh", 5},
  {"W", 1},
  {"kW", 2},
  {"VA", 2},
  {"kVA", 3},
  {"var", 3},
  {"kvar", 4},
  {"A", 1},
  {"V", 1},
  {"Celsius", 7},
  {"Fahrenheit", 10},
  {"K", 1},
  {"Percent", 7}
};

static const ocpp_string m_charge_profile[OCPP_CHARGING_MAX] =
{
  {"chargingProfileId", 17},
  {"transactionId", 13},
  {"stackLevel", 10},
  {"chargingProfilePurpose", 22},
  {"chargingProfileKind", 19},
  {"recurrencyKind", 14},
  {"validFrom", 9},
  {"validTo", 7},
  {"chargingSchedule", 16},
};

static const ocpp_string m_charge_profile_purpose[OCPP_CHARGING_PROFILE_MAX] =
{
  {"ChargePointMaxProfile", 21},
  {"TxDefaultProfile", 16},
  {"TxProfile", 9},
};

static const ocpp_string m_charge_profile_kind_type[OCPP_CHARGING_PROFILE_KIND_TYPE_MAX] =
{
  {"Absolute", 8},
  {"Recurring", 9},
  {"Relative", 8},
};

static const ocpp_string m_recurrency_kind_type[OCPP_RECURRENCY_KIND_TYPE_MAX] =
{
  {"Daily", 5},
  {"Weekly", 6},
};

static const ocpp_string m_charging_schedule[OCPP_CHARGING_SCHEDULE_MAX] =
{
  {"duration", 8},
  {"startSchedule", 13},
  {"chargingRateUnit", 16},
  {"chargingSchedulePeriod", 22},
  {"minChargingRate", 15},
};
/*
static const ocpp_string m_charging_rate_unit[OCPP_CHARGING_RATE_UINT_MAX] =
{
  {"W", 1};
  {"A", 1};
};

static const ocpp_string m_charging_schedule_priod[OCPP_CHARGING_SCHEDULE_PERIOD_MAX] =
{
  {"startPeriod", 11};
  {"limit", 5};
  {"numberPhases", 12};
};
*/
static const ocpp_type m_msg_type[MSG_TYPE_LIST] =
{
  {'2', 1}, // 2
  {'3', 1}, // 3
  {'4', 1}, // 4
};

static uint8_t m_frame_buffer[OCPP_CORE_FRAME_SIZE] = {0};

static void getRfidUid(uint8_t *pUid)
{
  uint8_t mm_test_id[4] = {0xAA, 0xBB, 0xCC, 0xDD};
  memcpy(pUid, mm_test_id, 4);
}

static void ocppAddMsgType(ocpp_frame *pFrame, ocpp_message_type pType)
{
  pFrame->buf[pFrame->used_len] = '[';
  pFrame->used_len = pFrame->used_len + 1;

  pFrame->buf[pFrame->used_len] = m_msg_type[pType].data;
  pFrame->used_len = pFrame->used_len + m_msg_type[pType].len;

  pFrame->buf[pFrame->used_len] = ',';
  pFrame->used_len = pFrame->used_len + 1;

  pFrame->remain = pFrame->size - pFrame->used_len;

}

static void ocppAddId(ocpp_frame *pFrame, uint8_t* pId)
{
  uint8_t mm_buf[64] = {0}, mm_len = sprintf(mm_buf, pId);

  pFrame->buf[pFrame->used_len] = (uint8_t)'\"';
  pFrame->used_len = pFrame->used_len + 1;

  memcpy(&pFrame->buf[pFrame->used_len], mm_buf, mm_len);
  pFrame->used_len = pFrame->used_len + mm_len;

  pFrame->buf[pFrame->used_len] = (uint8_t)'\"';
  pFrame->used_len = pFrame->used_len + 1;

  pFrame->buf[pFrame->used_len] = ',';
  pFrame->used_len = pFrame->used_len + 1;

  pFrame->remain = pFrame->size - pFrame->used_len;

}

static void ocppAddAction(ocpp_frame *pFrame, ocpp_core_action_list pAction)
{
  pFrame->buf[pFrame->used_len] = (uint8_t)'\"';
  pFrame->used_len = pFrame->used_len + 1;

  memcpy(&pFrame->buf[pFrame->used_len], m_core_action[pAction].data, m_core_action[pAction].len);
  pFrame->used_len = pFrame->used_len + m_core_action[pAction].len;

  pFrame->buf[pFrame->used_len] = (uint8_t)'\"';
  pFrame->used_len = pFrame->used_len + 1;

  pFrame->buf[pFrame->used_len] = ',';
  pFrame->used_len = pFrame->used_len + 1;

  pFrame->remain = pFrame->size - pFrame->used_len;
}

static void ocppAddPayload(ocpp_frame *pFrame, char *pPayload)
{
  char mm_buf[512] = {0};
  int mm_len = sprintf(mm_buf, pPayload);

  if(mm_len < 512)
  {
    memcpy(&pFrame->buf[pFrame->used_len], pPayload, mm_len);
    pFrame->used_len = pFrame->used_len + mm_len;

    pFrame->buf[pFrame->used_len] = (uint8_t)']';
    pFrame->used_len = pFrame->used_len + 1;

    pFrame->remain = pFrame->size - pFrame->used_len;
  }
  else
  {
        // out off range
  }

}

static void makeChargingSchedule(cJSON* pJson)
{

}

static void makeChargingProfile(cJSON* pJson)
{
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_PROFILE_ID].data, (char const*)t_profile_id);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_TRANSACTION_ID].data, (char const*)t_transactionId);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_STACK_LEVEL].data, (char const*)t_stack_level);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_PURPOSE].data, (char const*)t_profile_id);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_KIND].data, (char const*)t_profile_id);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_RECURRENCY_KIND].data, (char const*)t_profile_id);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_VALID_FROM].data, (char const*)t_profile_id);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_VALID_TO].data, (char const*)t_profile_id);
  cJSON_AddStringToObject(pJson, m_charge_profile[OCPP_CHARGING_SCHEDULE].data, (char const*)t_profile_id);
}

static void ocppMakeCoreReq(ocpp_core_action_list pAction, cJSON* pJson)
{

  switch(pAction)
  {
    case OCPP_AUTHORIZE:
    {
      /*
      * FILED LIST : idTag
      * FIELD NAME : idTag
      * FIELD TYPE : IdToken / CiString20Type
      */
      uint8_t mm_id[4] = {0};

      getRfidUid(mm_id);

      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_ID_TAG].data, (char const*)mm_id);
    }
    break;
    case OCPP_BOOT_NOTIFICATION:
    {
      /*
      * FILED LIST : chargeBoxSerialNumber / chargePointModel / chargePointSerialNumber
      *              chargePointVendor / firmwareVersion / iccid / imsi / meterSerialNumber
      *              meterType
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CHARGE_BOX_SERIAL_NUMBER].data, t_chargeBoxSerialNumber);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CHARGE_POINT_MODEL].data, t_chargePointModel);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CHARGE_POINT_SERIAL_NUMBER].data, t_chargePointVendor);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CHARGE_POINT_VENDOR].data, t_chargePointSerialNumber);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_FIRMWARE_VERSION].data, t_firmwareVersion);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_ICCID].data, t_iccid);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_IMSI].data, t_imsi);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_METER_SERIAL_NUMBER].data, t_meterSerialNumber);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_METER_TYPE].data, t_meterType);
    }
    break;
    case OCPP_CAHNGE_ACAILABILITY:
    {
      /*
      * FILED LIST : connectorId / type
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CONNECTOR_ID].data, t_connectorId);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_TYPE].data, t_type);
    }
    break;
    case OCPP_CAHNGE_CONFIGURATION:
    {
      /*
      * FILED LIST : key / value
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_KEY].data, t_key);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_VALUE].data, t_value);
    }
    break;
    case OCPP_CLEAR_CACHE:
    {
      /*
      * FILED LIST : status
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_STATUS].data, m_clear_cachce_status[OCPP_CLEAR_CACHE_ACCEPTED].data);
    }
    break;
    case OCPP_DATA_TRANSFER:
    {
      /*
      * FILED LIST : vendorId / messageId / data
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_VENDOR_ID].data, t_vendorID);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_MESSAGE_ID].data, t_messageID);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_DATA].data, t_data);
    }
    break;
    case OCPP_GET_CONFIGURATION:
    {
      /*
      * FILED LIST : key
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_KEY].data, t_key);
    }
    break;
    case OCPP_HEARTBEAT:
    {
      /*
      * not define
      */
    }
    break;
    case OCPP_METER_VALUES:
    {
      /*
      * FILED LIST : connectorId / transactionId / meterValue
      */
#if 0
      cJSON mm_time_body*, mm_time_list*, mm_s_v_body*, mm_s_v_list*;

      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CONNECTOR_ID].data, t_connectorId);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_TRANSACTION_ID].data, t_transactionId);
      cJSON_AddItemToObject(pJson, m_filed_req_name[OCPP_REQ_METER_VALUE].data, mm_time_body = cJSON_CreateArray());
      cJSON_AddItemToArray(mm_time_body, mm_time_list = cJSON_CreateObject());
      cJSON_AddStringToObject(mm_time_list, m_filed_req_name[OCPP_REQ_TIMESTAMP].data, t_time);
      cJSON_AddItemToObject(mm_time_list, m_filed_req_name[OCPP_REQ_SAMPLE_VALUE].data, mm_s_v_body = cJSON_CreateArray());
      cJSON_AddItemToArray(mm_s_v_body, mm_s_v_list = cJSON_CreateObject());
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_VALUE].data, t_value);
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_CONTEXT].data, m_reading_context[OCPP_READING_CONTEXT_OTHER].data);
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_FORMAT].data, m_value_format[OCPP_VALUE_FORMAT_RAW].data);
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_MEASURAND].data, m_measurand[OCPP_MEASURAND_CURRENT_EXPORT].data);
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_PHASE].data, m_phase[OCPP_PHASE_L1].data);
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_LOCATION].data, m_location[OCPP_LOCATION_OUTLET].data);
      cJSON_AddStringToObject(mm_s_v_body, m_smaple_value[OCPP_SAMPLE_VALUE_UNIT].data, m_unit_of_measure[OCPP_UNIT_OF_MEASURE_WH].data);
#endif
    }
    break;
    case OCPP_REMOTE_START_TRANSACTION:
    {
      /*
      * FILED LIST : connectorId / idTag / chargingProfile
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CONNECTOR_ID].data, t_connectorId);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_ID_TAG].data, t_idTag);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_METER_START].data, t_data);
      // get charging TxProfile
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_TIMESTAMP].data, t_data);
    }
    break;
    case OCPP_REMOTE_STOP_TRANSACTION:
    {

    }
    break;
    case OCPP_RESET:
    {

    }
    break;
    case OCPP_START_TRANSACTION:
    {
      /*
      * FILED LIST : connectorId / idTag / chargingProfile
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CONNECTOR_ID].data, t_connectorId);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_ID_TAG].data, t_idTag);

    }
    break;
    case OCPP_STATUS_NOTIFICATION:
    {
      /*
      * FILED LIST : connectorId / errCode / info / status / timestamp
      *              vendorId / vendorErrorCode
      */
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_CONNECTOR_ID].data, t_connectorId);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_ERROR_CODE].data, m_charge_point_error_code[OCPP_NO_ERROR].data);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_INFO].data, t_connectorId);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_STATUS].data, m_charge_point_status[OCPP_STATUS_AVAILABLE].data);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_TIMESTAMP].data, t_timestamp);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_VENDOR_ID].data, t_vendorID);
      cJSON_AddStringToObject(pJson, m_filed_req_name[OCPP_REQ_VENDOR_ERROR_CODE].data, t_vendor_error_code);
    }
    break;
    case OCPP_UNLOCK_CONNECTION:
    {

    }
    break;
    case OCPP_STOP_TRANSACTION:
    {

    }
    break;
    default:
    break;
  }
}

static void ocppMakeCoreConf(ocpp_core_action_list pAction, cJSON* pJson)
{
  switch(pAction)
  {
    case OCPP_AUTHORIZE:
    break;
    case OCPP_BOOT_NOTIFICATION:
    break;
    case OCPP_CAHNGE_ACAILABILITY:
    break;
    case OCPP_CAHNGE_CONFIGURATION:
    break;
    case OCPP_CLEAR_CACHE:
    break;
    case OCPP_DATA_TRANSFER:
    break;
    case OCPP_GET_CONFIGURATION:
    break;
    case OCPP_HEARTBEAT:
    break;
    case OCPP_METER_VALUES:
    break;
    case OCPP_REMOTE_START_TRANSACTION:
    break;
    case OCPP_REMOTE_STOP_TRANSACTION:
    break;
    case OCPP_RESET:
    break;
    case OCPP_START_TRANSACTION:
    break;
    case OCPP_STATUS_NOTIFICATION:
    break;
    case OCPP_UNLOCK_CONNECTION:
    break;
    case OCPP_STOP_TRANSACTION:
    break;
    default:
    break;
  }
}

static void ocppMakeCorePayload(ocpp_select_messages_list pSelect, ocpp_core_action_list pAction, cJSON* pJson)
{
    if(pSelect == OCPP_REQ) ocppMakeCoreReq(pAction, pJson);
    else if (pSelect == OCPP_CONF) ocppMakeCoreConf(pAction, pJson);
    else{ /* unkown select */ }
}

ocpp_frame ocppMakeCallFrame(ocpp_message_type pType, uint8_t* pId, ocpp_core_action_list pAction, ocpp_select_messages_list pSelect)
{
  char*  mm_payload;
  cJSON  mm_json;
  cJSON* mm_root = &mm_json;

  mm_root = cJSON_CreateObject();

  ocpp_frame mm_ocpp_frame =
  {
      .size     = OCPP_CORE_FRAME_SIZE,
      .used_len = 0,
      .remain   = OCPP_CORE_FRAME_SIZE,
  };

  mm_ocpp_frame.buf = m_frame_buffer;
  // clear buffer
  memset(mm_ocpp_frame.buf, 0x00, sizeof(m_frame_buffer));

  ocppAddMsgType(&mm_ocpp_frame, pType);
  ocppAddId(&mm_ocpp_frame, pId);
  ocppAddAction(&mm_ocpp_frame, pAction);
  ocppMakeCorePayload(pSelect, pAction, mm_root);

  /* improve ???*/
  mm_payload = cJSON_Print(mm_root);

  ocppAddPayload(&mm_ocpp_frame, mm_payload);

  cJSON_Delete(mm_root);

  return mm_ocpp_frame;
}

void ocpp_test(void)
{
    printf("ocpp test in\r\n");

    ocpp_frame mmFrame = ocppMakeCallFrame(CALL, "Hello", OCPP_BOOT_NOTIFICATION, OCPP_REQ);
    printf("%s\r\n", mmFrame.buf);
}
/*
int main(int argc, const char **argv)
{
    ocpp_test();
}
*/
