#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define OCPP_OPTIONAL 0
#define OCPP_CORE_FRAME_SIZE 1024

typedef enum {
    CALL = 0,        // Client to Server
    CALLRESULT,      // Server to Client
    CALLERROR,       // Server to Client
    MST_TYPE_INVALID,
    MSG_TYPE_LIST
}ocpp_message_type;

typedef struct{

    char* buf;
    int size;
    int used;
    int remain;

}ocpp_msg_frame;

typedef enum{

  OCPP_AUTHORIZE = 0,            // Authorize,
  OCPP_BOOT_NOTIFICATION,        // BootNotification,
  OCPP_CAHNGE_ACAILABILITY,      // ChangeAvailability,
  OCPP_CAHNGE_CONFIGURATION,     // ChangeConfiguration,
  OCPP_CLEAR_CACHE,              // ClearCache,
  OCPP_DATA_TRANSFER,            // DataTransfer,
  OCPP_GET_CONFIGURATION,        // GetConfiguration,
  OCPP_HEARTBEAT,                // Heartbeat
  OCPP_METER_VALUES,             // meterVales,
  OCPP_REMOTE_START_TRANSACTION, // RemoteStartTransaction,
  OCPP_REMOTE_STOP_TRANSACTION,  // RemoteStopTransaction,
  OCPP_RESET,                    // Reset,
  OCPP_START_TRANSACTION,        // StartTransaction,
  OCPP_STATUS_NOTIFICATION,      // StatusNotification,
  OCPP_STOP_TRANSACTION,         // StopTransaction,
  OCPP_UNLOCK_CONNECTION,        // UnlockConnector,
  OCPP_CORE_ACTION_MAX,          // CoreActionList

}ocpp_core_action_list;

typedef enum{

  OCPP_REQ = 0,
  OCPP_CONF

}ocpp_select_messages_list;

typedef enum{

  OCPP_REQ_ID_TAG = 0,                     // idTag
  OCPP_REQ_CHARGE_BOX_SERIAL_NUMBER,   // chargeBoxSerialNumber
  OCPP_REQ_CHARGE_POINT_MODEL,         // chargePointModel
  OCPP_REQ_CHARGE_POINT_SERIAL_NUMBER, // chargePointSerialNumber
  OCPP_REQ_CHARGE_POINT_VENDOR,        // chargePointVendor
  OCPP_REQ_FIRMWARE_VERSION,           // firmwareVersion
  OCPP_REQ_ICCID,                      // iccid
  OCPP_REQ_IMSI,                       // imsi
  OCPP_REQ_METER_SERIAL_NUMBER,        // meterSerialNumber
  OCPP_REQ_METER_TYPE,                 // meterType
  OCPP_REQ_RESERVATION_ID,             // reservationId
  OCPP_REQ_CONNECTOR_ID,               // connectorId
  OCPP_REQ_TYPE,                       // type
  OCPP_REQ_KEY,                        // key
  OCPP_REQ_VALUE,                      // value
  OCPP_REQ_ID,                         // id
  OCPP_REQ_CHARGING_PROFILE_PURPOSE,   // chargingProfilePurpose
  OCPP_REQ_STACK_LEVEL,                // stackLevel
  OCPP_REQ_VENDOR_ID,                  // vendorId
  OCPP_REQ_MESSAGE_ID,                 // messageId
  OCPP_REQ_DATA,                       // data
  OCPP_REQ_STATUS,                     // status
  OCPP_REQ_DURATION,                   // duration
  OCPP_REQ_CHARING_RATE_UNIT,          // chargingRateUnit
  OCPP_REQ_LOACTION,                   // location
  OCPP_REQ_RETRIES,                    // retries
  OCPP_REQ_RETRY_INTERVAL,             // retryInterval
  OCPP_REQ_START_TIME,                 // startTime
  OCPP_REQ_STOP_TIME,                  // stopTime
  OCPP_REQ_TRANSACTION_ID,             // transactionId
  OCPP_REQ_METER_VALUE,                // meterValue
  OCPP_REQ_CHARGING_PROFILE,           // chargingProfile
  OCPP_REQ_EXPIRY_DATE,                // expiryDate
  OCPP_REQ_PARENT_ID_TAG,              // parentIdTag
  OCPP_REQ_LOCAL_AUTHORIZATION_LIST,   // localAuthorizationList
  OCPP_REQ_UPDATE_TYPE,                // updateType
  OCPP_REQ_CS_CHARGING_PROFILES,       // csChargingProfiles
  OCPP_REQ_METER_START,                // meterStart
  OCPP_REQ_TIMESTAMP,                  // timestamp
  OCPP_REQ_ERROR_CODE,                 // errorCode
  OCPP_REQ_INFO,                       // info
  OCPP_REQ_VENDOR_ERROR_CODE,          // vendorErrorCode
  OCPP_REQ_METER_STOP,                 // meterStop
  OCPP_REQ_REASON,                     // reason
  OCPP_REQ_TRANSACTION_DATA,           // transactionData
  OCPP_REQ_REQUESTED_MESSAGE,          // requestedMessage
  OCPP_REQ_RETRIEVE_DATE,              // retrieveDate
  OCPP_REQ_SAMPLE_VALUE,                // smapleVale
  OCPP_REQ_MESSAGES_MAX

}ocpp_req_messages_list;

typedef enum{

  OCPP_CONF_ID_TAG_INFO,       // idTagInfo
  OCPP_CONF_CURRENT_TIME,      // currentTime
  OCPP_CONF_INTERVAL,          // interval
  OCPP_CONF_STATUS,            // status
  OCPP_CONF_DATA,              // data
  OCPP_CONF_CONNECTOR_ID,      // connectorId
  OCPP_CONF_SCHEDULE_START,    // scheduleStart
  OCPP_CONF_CHARGING_SCHEDULE, // chargingSchedule
  OCPP_CONF_CONFIGURATION_KEY, // configurationKey
  OCPP_CONF_UNKNOWN_KEY,       // unknownKey
  OCPP_CONF_FILE_NAME,         // fileName
  OCPP_CONF_LIST_VERSION,      // listVersion
  OCPP_CONF_TRANSACTION_ID,    // transactionId
  OCPP_CONF_MESSAGES_MAX

}ocpp_conf_messages_list;

typedef enum{
  OCPP_ERR_CONNECTOR_LOCK,      // ConnectorLockFailure
  OCPP_ERR_EV_COMMUNICATION,    // EVCommunicationError
  OCPP_ERR_GROUND,              // GroundFailure
  OCPP_ERR_HIGH_TEMP,           // HighTemperature
  OCPP_ERR_INTERNAL,            // InternalError
  OCPP_ERR_LOCAL_LIST_CONFLICT, // LocalListConflict
  OCPP_NO_ERROR,                // NoError
  OCPP_ERR_OTHER,               // OtherError
  OCPP_ERR_OVER_CURRENT,        // OverCurrentFailure
  OCPP_ERR_OVER_VOLTAGE,        // OverVoltage
  OCPP_ERR_POWER_METER,         // PowerMeterFailure
  OCPP_ERR_POWER_SWITCH,        // PowerSwitchFailure
  OCPP_ERR_READER,              // ReaderFailure
  OCPP_ERR_RESET,               // ResetFailure
  OCPP_ERR_UNDER_VOLTAGE,       // UnderVoltage
  OCPP_ERR_WEAK_SIGNAL,         // WeakSignal
  OCPP_ERR_MAX
}ocpp_charge_point_error_code_list;

typedef enum{
  OCPP_STATUS_AVAILABLE,      // Available
  OCPP_STATUS_PREPARING,      // Preparing
  OCPP_STATUS_CHARGING,       // Charging
  OCPP_STATUS_SUSPENDED_EVSE, // SuspendedEVSE
  OCPP_STATUS_SUSPENDED_EV,   // SuspendedEV
  OCPP_STATUS_FINISHING,      // Finishing
  OCPP_STATUS_RESERVED,       // Reserved
  OCPP_STATUS_UNAVAILABLE,    // Unavailable
  OCPP_STATUS_FAULTED,        // Faulted
  OCPP_STATUS_MAX
}ocpp_charge_point_status_list;

typedef enum{
  OCPP_CLEAR_CACHE_ACCEPTED, // Accepted,
  OCPP_CLEAR_CACHE_REJECTED, // Rejected,
  OCPP_CLEAR_CACHE_MAX
}ocpp_clear_cache_status_list;

typedef enum{
  OCPP_SAMPLE_VALUE_VALUE,     // value
  OCPP_SAMPLE_VALUE_CONTEXT,   // context
  OCPP_SAMPLE_VALUE_FORMAT,    // format
  OCPP_SAMPLE_VALUE_MEASURAND, // measurand
  OCPP_SAMPLE_VALUE_PHASE,     // phase
  OCPP_SAMPLE_VALUE_LOCATION,  // location
  OCPP_SAMPLE_VALUE_UNIT,      // unit
  OCPP_SAMPLE_VALUE_MAX
}ocpp_sample_value_list;

typedef enum{
  OCPP_READING_CONTEXT_INTERRUPT_BEGIN, //
  OCPP_READING_CONTEXT_INTERRUPT_END, //
  OCPP_READING_CONTEXT_OTHER, //
  OCPP_READING_CONTEXT_SAMPLE_CLOCK, //
  OCPP_READING_CONTEXT_SAMPLE_PERIODIC, //
  OCPP_READING_CONTEXT_TRANSACTION_BEGIN, //
  OCPP_READING_CONTEXT_TRANSACTION_END, //
  OCPP_READING_CONTEXT_TRIGGER, //
  OCPP_READING_CONTEXT_MAX
}ocpp_reading_context_list;

typedef enum{
  OCPP_VALUE_FORMAT_RAW, //
  OCPP_VALUE_FORMAT_SIGNED_DATA, //
  OCPP_VALUE_FORMAE_MAX
}ocpp_value_format_list;

typedef enum
{
  OCPP_MEASURAND_CURRENT_EXPORT, //
  OCPP_MEASURAND_CURRENT_IMPORT, //
  OCPP_MEASURAND_CURRENT_OFFERED, //
  OCPP_MEASURAND_ENERGY_ACTIVE_EXPORT_REGISTER, //
  OCPP_MEASURAND_ENERGY_ACTIVE_IMPORT_REGISTER, //
  OCPP_MEASURAND_ENERGY_REACTIVE_EXPORT_REGISTER, //
  OCPP_MEASURAND_ENERGY_REACTIVE_IMPORT_REGISTER, //
  OCPP_MEASURAND_ENERGY_ACTIVE_EXPORT_INTERVAL, //
  OCPP_MEASURAND_ENERGY_ACTIVE_IMPORT_INTERVAL, //
  OCPP_MEASURAND_ENERGY_REACTIVE_EXPORT_INTERVAL, //
  OCPP_MEASURAND_ENERGY_REACTIVE_IMPORT_INTERVAL, //
  OCPP_MEASURAND_FREQUENCY, //
  OCPP_MEASURAND_POWER_ACTIVE_EXPORT, //
  OCPP_MEASURAND_POWER_ACTIVE_IMPORT, //
  OCPP_MEASURAND_POWER_FACTOR, //
  OCPP_MEASURAND_POWER_OFFERED, //
  OCPP_MEASURAND_POWER_REACTIVE_EXPORT, //
  OCPP_MEASURAND_POWER_REACTIVE_IMPORT, //
  OCPP_MEASURAND_RPM, //
  OCPP_MEASURAND_SOC, //
  OCPP_MEASURAND_TEMPERATURE, //
  OCPP_MEASURAND_VOLTAGE, //
  OCPP_MEASURAND_MAX
}ocpp_measurand_list;

typedef enum{
  OCPP_PHASE_L1, //
  OCPP_PHASE_L2, //
  OCPP_PHASE_L3, //
  OCPP_PHASE_N, //
  OCPP_PHASE_L1_N, //
  OCPP_PHASE_L2_N, //
  OCPP_PHASE_L3_N, //
  OCPP_PHASE_L1_L2, //
  OCPP_PHASE_L2_L3, //
  OCPP_PHASE_L3_L1, //
  OCPP_PHASE_MAX

}ocpp_phase_list;

typedef enum{
  OCPP_LOCATION_BODY, // default value, body
  OCPP_LOCATION_CABLE, //
  OCPP_LOCATION_EV, //
  OCPP_LOCATION_INLET, //
  OCPP_LOCATION_OUTLET, //
  OCPP_LOCATION_MAX
}ocpp_location_list;

typedef enum{
  OCPP_UNIT_OF_MEASURE_WH, //
  OCPP_UNIT_OF_MEASURE_KWH, //
  OCPP_UNIT_OF_MEASURE_VARH, //
  OCPP_UNIT_OF_MEASURE_KVARH, //
  OCPP_UNIT_OF_MEASURE_W, //
  OCPP_UNIT_OF_MEASURE_KW, //
  OCPP_UNIT_OF_MEASURE_VA, //
  OCPP_UNIT_OF_MEASURE_KVA, //
  OCPP_UNIT_OF_MEASURE_VAR, //
  OCPP_UNIT_OF_MEASURE_KVAR, //
  OCPP_UNIT_OF_MEASURE_A, //
  OCPP_UNIT_OF_MEASURE_V, //
  OCPP_UNIT_OF_MEASURE_CELSIUS, //
  OCPP_UNIT_OF_MEASURE_FAHRENHEIT, //
  OCPP_UNIT_OF_MEASURE_K, //
  OCPP_UNIT_OF_MEASURE_PERCENT, //
  OCPP_UNIT_OF_MEASURE_MAX
}ocpp_unit_of_measure_list;

typedef enum{
  OCPP_CHARGING_PROFILE_ID, //
  OCPP_CHARGING_TRANSACTION_ID, //
  OCPP_CHARGING_STACK_LEVEL, //
  OCPP_CHARGING_PURPOSE, //
  OCPP_CHARGING_KIND, //
  OCPP_CHARGING_RECURRENCY_KIND, //
  OCPP_CHARGING_VALID_FROM, //
  OCPP_CHARGING_VALID_TO, //
  OCPP_CHARGING_SCHEDULE, //
  OCPP_CHARGING_MAX, //
}ocpp_charge_profile_list;

typedef enum{
  OCPP_CHARGING_MAX_PROFILE_PURPOSE,
  OCPP_CHARGING_DEFAULT_PROFILE_PURPOSE,
  OCPP_CHARGING_TX_PROFILE_PURPOSE,
  OCPP_CHARGING_PROFILE_MAX
}ocpp_charge_profile_purpose_list;

typedef enum{
  OCPP_CHARGING_PROFILE_KIND_TYPE_ABSOLUTE,
  OCPP_CHARGING_PROFILE_KIND_TYPE_RECURRING,
  OCPP_CHARGING_PROFILE_KIND_TYPE_RELATIVE,
  OCPP_CHARGING_PROFILE_KIND_TYPE_MAX
}ocpp_charge_profile_kind_type_list;

typedef enum{
  OCPP_RECURRENCY_KIND_TYPE_DAILY,
  OCPP_RECURRENCY_KIND_TYPE_WEEKLY,
  OCPP_RECURRENCY_KIND_TYPE_MAX
}ocpp_recurrency_kind_type_list;

typedef enum{
  OCPP_CHARGING_DURATION,
  OCPP_CHARGING_START_SCHEDULE,
  OCPP_CHARGING_RATE_UNIT,
  OCPP_CHARGING_SCHEDULE_PERIOD,
  OCPP_CHARGING_MIN_RATE,
  OCPP_CHARGING_SCHEDULE_MAX,
}ocpp_charging_schedule_list;

typedef enum{
  OCPP_CHARGING_RATE_UINT_W,
  OCPP_CHARGING_RATE_UINT_H,
  OCPP_CHARGING_RATE_UINT_MAX,
}ocpp_charging_rate_unit_list;

typedef enum{
  OCPP_CHARGING_SCHEDULE_PERIOD_START,
  OCPP_CHARGING_SCHEDULE_PERIOD_LIMIT,
  OCPP_CHARGING_SCHEDULE_PERIOD_NUMBER_PHASE,
  OCPP_CHARGING_SCHEDULE_PERIOD_MAX
}ocpp_charging_schedule_priod_list;
/*
typedef struct{

    uint8_t*  buf;
    uint8_t   used_len;
    uint8_t   remain;

    const uint8_t size;

}ocpp_frame;
*/
typedef struct{

    uint8_t* uniqueId;
    uint8_t* action;
    uint8_t* payload;

}ocpp_call_frame;

typedef struct{

    uint8_t* uniqueId;
    uint8_t* payload;

}ocpp_call_result_frame;

typedef struct{

    uint8_t* uniqueId;
    uint8_t* err_code;
    uint8_t* err_desc;
    uint8_t* payload;

}ocpp_call_error_frame;

typedef struct{

  const char* data;
  uint8_t  len;

}ocpp_string;

typedef struct{

  int      data;
  uint8_t  len;

}ocpp_type;

typedef struct{

    uint8_t  msg_type;

    union {
        uint8_t* mem;
        struct
        {
            uint8_t   used_len;
            int       remain;
            const int size;
            uint8_t*  buf;
        };
        struct
        {
            ocpp_call_frame call;
        };
        struct
        {
            ocpp_call_result_frame callResult;
        };
        struct
        {
            ocpp_call_error_frame callError;
        };
    };

}ocpp_frame;

void ocpp_test(void);
ocpp_frame ocppMakeCallFrame(ocpp_message_type pType, uint8_t* pId, ocpp_core_action_list pAction, ocpp_select_messages_list pSelect);
ocpp_frame* ocpp_parse_frame(char* payload, int len);
