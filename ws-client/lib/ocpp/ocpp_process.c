#include <stdio.h>
#include <stdlib.h>

#include "ocpp_process.h"
#include "ocpp_1_6_j.h"

#include "../json/cJSON.h"
#include "../../src/noodoe_client.h"

/*
  CS_CANCEL_RESERVATION = 0,   // CancelReservation
  CS_CAHNGE_AVAILABILITY,      // ChangeAvailability,
  CS_CHANGE_CONFIGURATION,        // ChangeConfiguration,
  CS_CLEAR_CACHE,              // ,
  CS_CLEAR_CHARGING_PROFILE,   // ,
  CS_DATA_TRANSFER,            // DataTransfer,
  CS_GET_COMPOSITE_SCHEDULE    // GetCompositeSchedule,
  CS_GET_CONFIGURATION,        // GetConfiguration,
  CS_GET_DIAGNOSTICS,          // GetDiagnostics,
  CS_GET_LOCAL_LIST_VERSION    // GetLocalListVersion,
  CS_REMOTE_START_TRANSACTION, // RemoteStartTransaction,
  CS_REMOTE_STOP_TRANSACTION,  // RemoteStopTransaction,
  CS_RESET_NOW,                // ResetNow,
  CS_RESET,                    // Reset,
  CS_SEND_LOCAL_LIST,          // SendLocalList,
  CS_SET_CAHRGING_PROFILE,     // SetChargingProfile,
  CS_TRIGGER_MESSAGE,          // TriggerMessage
  CS_UNLOCK_CONNECTOR,         // UnlockConnector,
  CS_CORE_ACTION_MAX,          // CoreActionList
*/
static const ocpp_string m_core_action[CS_CORE_ACTION_MAX] =
{
  {"CancelReservation", 17},
  {"ChangeAvailability", 18},
  {"ChangeConfiguration", 16},
  {"ClearCache", 10},
  {"ClearChargingProfile", 20},
  {"DataTransfer", 12},
  {"GetCompositeSchedule", 20},
  {"GetConfiguration", 16},
  {"GetDiagnostics", 14},
  {"GetLocalListVersion", 19},
  {"RemoteStartTransaction", 22},
  {"RemoteStopTransaction", 21},
  {"ResetNow", 8},
  {"Reset", 5},
  {"SendLocalList", 13},
  {"SetChargingProfile", 18},
  {"TriggerMessage", 14},
  {"UnlockConnector", 15}
};


static char mWriteMem[OCPP_CORE_FRAME_SIZE] = {0};
static char mReadMem[OCPP_CORE_FRAME_SIZE] = {0};

ocpp_frame mReadFrame =
{
	.size     = OCPP_CORE_FRAME_SIZE,
	.used_len = 0,
	.remain   = OCPP_CORE_FRAME_SIZE,
	.mem      = mReadMem,
};

#define OP_CALL       '2'
#define OP_CALLRESULT '3'
#define OP_CALLERROR  '4'

// call        header : [<MessageTypeId>, "<UniqueId>", "<Action>", {<Payload>}]
// call result header : [<MessageTypeId>, "<UniqueId>", {<Payload>}]
// call error  header : [<MessageTypeId>, "<UniqueId>", "<errorCode>", "<errorDescription>", {<errorDetails>}]

void init_frame(ocpp_frame* pFrame, char* pSrc, int pLen, int msgTyep)
{
	if(pLen > OCPP_CORE_FRAME_SIZE)
		printf("%s : out of len\n", __func__);

	int i = 0, mmCommaList = 0, mmParantheseList = 0;

	uint8_t mmUniqueIdLen = 0, mmActionLen = 0, mmErrorCodeLen = 0, mmErrorDescLen = 0;

	switch(msgTyep)
	{
		case OP_CALL :
		{
			for(i = 0; i <= pLen; i++)
			{
				if(pSrc[i] == ',')
				{
					mmCommaList++;
				}

				switch(mmCommaList)
				{
					case 1:
					{
						if((pSrc[i] != ' ') & (pSrc[i] != ',') & (pSrc[i] != '\"'))
						{
							mmUniqueIdLen++;
						}
					}
					break;
					case 2:
					{
						if((pSrc[i] != ' ') & (pSrc[i] != ',') & (pSrc[i] != '\"'))
						{
							mmActionLen++;
						}
					}
					break;
					default:
					break;
				}

				if(mmCommaList == 3)
					break;
			}

			pFrame->call.uniqueId = &pFrame->mem[0];
			pFrame->call.action   = &pFrame->mem[mmUniqueIdLen + 1];
			pFrame->call.payload  = &pFrame->mem[(mmUniqueIdLen + mmActionLen + 2)];
			printf("%s: uniqueId Len(%d) , action Len(%d), total(%d)\n", __func__, mmUniqueIdLen, mmActionLen, (mmUniqueIdLen + mmActionLen + 2));
		}
		break;
		case OP_CALLRESULT :
		{
			for(i = 0; i <= pLen; i++)
			{
				if(pSrc[i] == ',')
				{
					mmCommaList++;
				}

				switch(mmCommaList)
				{
					case 1:
					{
						if((pSrc[i] != ' ') & (pSrc[i] != ',') & (pSrc[i] != '\"'))
						{
							mmUniqueIdLen++;
						}
					}
					break;
					default:
					break;
				}

				if(mmCommaList == 2)
					break;
			}

			pFrame->callResult.uniqueId = &pFrame->mem[0];
			pFrame->callResult.payload = &pFrame->mem[mmUniqueIdLen + 1];
			printf("%s: uniqueId Len(%d)\n", __func__, mmUniqueIdLen);
		}
		break;
		case OP_CALLERROR :
		{
			for(i = 0; i <= pLen; i++)
			{
				if(pSrc[i] == ',')
				{
					mmCommaList++;
				}

				switch(mmCommaList)
				{
					case 1:
					{
						if((pSrc[i] != ' ') & (pSrc[i] != ',') & (pSrc[i] != '\"'))
						{
							mmUniqueIdLen++;
						}
					}
					break;
					case 2:
					{
						if((pSrc[i] != ' ') & (pSrc[i] != ',') & (pSrc[i] != '\"'))
						{
							mmErrorCodeLen++;
						}
					}
					break;
					case 3:
					{
						if((pSrc[i] != ' ') & (pSrc[i] != ',') & (pSrc[i] != '\"'))
						{
							mmErrorDescLen++;
						}
					}
					break;
					default:
					break;
				}

				if(mmCommaList == 4)
					break;
			}

			pFrame->callError.uniqueId = &pFrame->mem[0];
			pFrame->callError.err_code = &pFrame->mem[(mmUniqueIdLen + 1)];
			pFrame->callError.err_desc = &pFrame->mem[(mmUniqueIdLen + mmErrorCodeLen + 2)];
			pFrame->callError.payload  = &pFrame->mem[(mmUniqueIdLen + mmErrorCodeLen + mmErrorDescLen + 3)];

			printf("%s: uniqueId Len(%d) , err code Len(%d), err desc Len(%d)\n",  \
						 __func__, mmUniqueIdLen, mmErrorCodeLen, mmErrorDescLen);
		}
		break;
		default:
			printf("%s : valid msg\n", __func__);
		break;
	}
}

int get_elements(char* pSrc, int pLen)
{
	int i = 0, mmElements = 0;

	for(i = 0; i <= pLen; i++)
	{
		if(pSrc[i] == ',')
			mmElements++;

		if(pSrc[i] == '{')
		{
			mmElements++;
			break;
		}
	}

	return mmElements;
}

void get_uniqueId(char* pSrc, int pLen, char* pId)
{
	const char COMMA = ',';

	int i = 0, j = 0, mmIdLen = 0, mmCommaList = 0;

	for(i = 0; i <= pLen; i++)
	{
		if(pSrc[i] == ',')
			mmCommaList++;

		if((mmCommaList == 1) & (pSrc[i]!=',') & (pSrc[i] != '\"'))
		{
			pId[j] = pSrc[i];
			j++;
		}

		if(mmCommaList == 2)
		{
			pId[j] = '\0';
			break;
		}
	}
	//printf("%s :len(%d)(%s)\n", __func__, j, pId);
}

void get_action(char* pSrc, int pLen, char* pAction)
{
	const char COMMA = ',';

	int i = 0, j = 0, mmCommaList = 0;

	for(i = 0; i <= pLen; i++)
	{
		if(pSrc[i] == ',')
			mmCommaList++;

		if((mmCommaList == 2) & (pSrc[i]!=',') & (pSrc[i] != '\"'))
		{
			pAction[j] = pSrc[i];
			j++;
		}

		if(mmCommaList == 3)
		{
			pAction[j] = '\0';
			break;
		}
	}
	//printf("%s :len(%d)(%s)\n", __func__, j, pAction);
}

void get_errCode(char* pSrc, int pLen, char* pErrCode)
{
	int i = 0, j = 0, mmCommaList = 0;

	for(i = 0; i <= pLen; i++)
	{
		if(pSrc[i] == ',')
			mmCommaList++;

		if((mmCommaList == 2) & (pSrc[i]!=',') & (pSrc[i] != '\"'))
		{
			pErrCode[j] = pSrc[i];
			j++;
		}

		if(mmCommaList == 3)
		{
			pErrCode[j] = '\0';
			break;
		}
	}
	//printf("%s :len(%d)(%s)\n", __func__, j, pErrCode);
}

void get_errDesc(char* pSrc, int pLen, char* pErrDesc)
{
	int i = 0, j = 0, mmCommaList = 0;

	for(i = 0; i <= pLen; i++)
	{
		if(pSrc[i] == ',')
			mmCommaList++;

		if((mmCommaList == 3) & (pSrc[i]!=',') & (pSrc[i] != '\"'))
		{
			pErrDesc[j] = pSrc[i];
			j++;
		}

		if(mmCommaList == 4)
		{
			pErrDesc[j] = '\0';
			break;
		}
	}
	//printf("%s :len(%d)(%s)\n", __func__, j, pErrDesc);
}


void get_payload(char* pSrc, int pLen, char* pPayload)
{
	int i = 0, j = 0, mmIdLen = 0, mmParantheseList = 0;

	for(i = 0; i < (pLen - 1); i++)
	{
		if(pSrc[i] == '{')
			mmParantheseList++;

		if(mmParantheseList == 1)
		{
			pPayload[j] = pSrc[i];
			j++;
		}
	}

	pPayload[j] = '\0';

	//printf("%s :len(%d)(%s)\n", __func__, j, pPayload);
}

int parse_frame(ocpp_frame* pFrame, char* pSrc, int pLen)
{

	const char COMMA = ',', L_PARANTHESES = '{', \
			     R__PARANTHESES = '}', L_BRACKETS = '[',R_BRACKETS = ']';

  char mmMsgType = '0';
  int mmLen = 0, i = 0, j = 0;
	int mm_msg_ret = MST_TYPE_INVALID;


	while(pSrc[i++]!='\0')
		mmLen++;

	// check len is valid
	if(pLen < 0 || pLen > mmLen)
	{
		printf("%s : invalid len (%d,%d)\n", __func__, pLen, mmLen);

		return mm_msg_ret;
	}

	/*find msg tyep
	 *  CALL       = 2, Client to Server, mapping to ocpp_message_type CALL
	 *	CALLRESULT = 3, Server to Client, mapping to ocpp_message_type CALLRESULT
	 *	CALLERROR  = 4, Server to Client, mapping to ocpp_message_type CALLERROR
	 */

	mmMsgType = (pSrc[0] == L_BRACKETS) ? pSrc[1] : MST_TYPE_INVALID;
	printf("%s : msg_type(%c)\n", __func__, mmMsgType);

	init_frame(pFrame, pSrc, pLen, mmMsgType);
	// chcek pSrc is valid msg

	switch(mmMsgType)
	{
		case OP_CALL :
		{
			int mmElements = get_elements(pSrc, pLen);
			printf("%s : check msg type (CALL) %d\n", __func__, mmElements);

			if(mmElements != 4)
				printf("%s : invalid elements\n", __func__);

			pFrame->msg_type = OP_CALL;

			get_uniqueId(pSrc, pLen, pFrame->call.uniqueId);
			get_action(pSrc, pLen, pFrame->call.action);
			get_payload(pSrc, pLen, pFrame->call.payload);
		}
		break;
		case OP_CALLRESULT :
		{
			int mmElements = get_elements(pSrc, pLen);
			printf("%s : check msg type (CALLRESULT) %d, %c\n", __func__, mmElements, pFrame->msg_type);

			if(mmElements != 3)
				printf("%s : invalid elements\n", __func__);

			pFrame->msg_type = OP_CALLRESULT;

			get_uniqueId(pSrc, pLen, pFrame->callResult.uniqueId);
			//printf("%s : %s, %c\n", __func__, pFrame->callResult.uniqueId, pFrame->msg_type);

			get_payload(pSrc, pLen, pFrame->callResult.payload);
			//printf("%s : %s, %c\n", __func__, pFrame->callResult.payload, pFrame->msg_type);

		}
		break;
		case OP_CALLERROR :
		{
			int mmElements = get_elements(pSrc, pLen);
			//printf("%s : check msg type (CALLERROR) %d\n", __func__, mmElements);

			if(mmElements != 5)
				printf("%s : invalid elements\n", __func__);

			pFrame->msg_type = OP_CALLERROR;
			get_uniqueId(pSrc, pLen, pFrame->callError.uniqueId);
			get_errCode(pSrc, pLen, pFrame->callError.err_code);
			get_errDesc(pSrc, pLen, pFrame->callError.err_desc);
			get_payload(pSrc, pLen, pFrame->callError.payload);
		}
		break;
		default:
			printf("%s : valid msg\n", __func__);
		break;
	};

	return mm_msg_ret;
}

int get_call_action_list(uint8_t* pAction)
{
	int i = -1;

	for(i = 0; i < CS_CORE_ACTION_MAX; i++)
		if(memcmp(m_core_action[i].data, pAction, m_core_action[i].len) == 0)
			break;

	return i;
}

void dispatch_call(uint8_t* pAction, uint8_t* pPayload)
{
	int doAction = get_call_action_list(pAction);

	printf("%s: %d\n", __func__, doAction);

	// clear memory
	memset(mWriteMem, 0x00, OCPP_CORE_FRAME_SIZE);

	ocpp_frame mm_ocpp_frame =
	{
		.size     = OCPP_CORE_FRAME_SIZE,
		.used_len = 0,
		.remain   = OCPP_CORE_FRAME_SIZE,
	};

	mm_ocpp_frame.mem = mWriteMem;

	//cJSON
	switch(doAction)
	{
		case CS_CANCEL_RESERVATION:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_CANCEL_RESERVATION, OCPP_CONF);
		}
		break;
		case CS_CAHNGE_AVAILABILITY:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_CAHNGE_AVAILABILITY, OCPP_CONF);
		}
		break;
		case CS_CLEAR_CACHE:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_CLEAR_CACHE, OCPP_CONF);
		}
		break;
		case CS_DATA_TRANSFER:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_DATA_TRANSFER, OCPP_CONF);
		}
		break;
		case CS_GET_COMPOSITE_SCHEDULE:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_GET_COMPOSITE_SCHEDULE, OCPP_CONF);
		}
		break;
		case CS_GET_CONFIGURATION:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_GET_CONFIGURATION, OCPP_CONF);
		}
		break;
		case CS_GET_DIAGNOSTICS:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_GET_DIAGNOSTICS, OCPP_CONF);
		}
		break;
		case CS_GET_LOCAL_LIST_VERSION:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_GET_LOCAL_LIST_VERSION, OCPP_CONF);
		}
		break;
		case CS_REMOTE_START_TRANSACTION:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_START_TRANSACTION, OCPP_CONF);
		}
		break;
		case CS_REMOTE_STOP_TRANSACTION:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_STOP_TRANSACTION, OCPP_CONF);
		}
		break;
		case CS_RESET_NOW:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_RESET_NOW, OCPP_CONF);
		}
		break;
		case CS_RESET:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_RESET, OCPP_CONF);
		}
		break;
		case CS_SEND_LOCAL_LIST:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_SEND_LOCAL_LIST, OCPP_CONF);
		}
		break;
		case CS_SET_CAHRGING_PROFILE:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_SET_CAHRGING_PROFILE, OCPP_CONF);
		}
		break;
		case CS_TRIGGER_MESSAGE:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_TRIGGER_MESSAGE, OCPP_CONF);
		}
		break;
		case CS_UNLOCK_CONNECTOR:
		{
			ocppMakeCallFrame(&mm_ocpp_frame, CALLRESULT, "FW-Tset01", CP_UNLOCK_CONNECTOR, OCPP_CONF);
		}
		break;
		default:
			printf("%s:Invalid action\n", __func__);
		break;
	}

	printf("%s:ocppMakeCallFrame : %s\n", __func__, mm_ocpp_frame.buf);
	noodoe_client_write(mm_ocpp_frame.buf, -1);

}

void dispatch_callResult(uint8_t* pPayload)
{

}

void dispatch_callErr(uint8_t* pPayload)
{

}

void dispatch_frame(ocpp_frame* pFrame)
{
	switch(pFrame->msg_type)
	{
		case OP_CALL :
		{
			dispatch_call(pFrame->call.action, pFrame->call.payload);
		}
		break;
		case OP_CALLRESULT :
		{
			dispatch_callResult(pFrame->callResult.payload);
		}
		break;
		case OP_CALLERROR :
		{
			dispatch_callErr(pFrame->callError.payload);
		}
		break;
		default:
			// never run in here.
			printf("%s : Invalid msg (%c)\n", __func__, pFrame->msg_type);
		break;
	};
}

int on_close(void* in, int len)
{
	printf("%s\n",__func__);
}

int on_write(void* in, int len)
{
	printf("%s\n",__func__);
}

int on_open(void* in, int len)
{
	printf("%s\n",__func__);
}

char testInBuf[512] = {0};
int on_receive_message(void* in, int len)
{

	char *mm_buf = (char*)in;
	memcpy(testInBuf, in, len);

	printf("%s start : (%d)\r\n",__func__, len);

	memset(mReadMem, 0x00, OCPP_CORE_FRAME_SIZE);

	parse_frame(&mReadFrame, testInBuf, len);
	dispatch_frame(&mReadFrame);
}

int on_send(void* in, int len)
{
	printf("%s\n",__func__);
}

#define TEST 0

/*
char * test = "[2,\"396e5858-4dd5-4013-a9c1-634713769e39\",\"GetConfiguration\",{\"key\":[]}]";
//char * test = "[3,\"FW-Tset01\",{\"currentTime\":\"2021-08-11T10:02:07.310Z\",\"interval\":300,\"status\":\"Accepted\"}]";

int main(int argc, const char **argv)
{

  printf("%s in \n", __func__);

//    ocpp_test();

	printf("%s start make call frame\n", __func__);

  memset(mWriteMem, 0x00, OCPP_CORE_FRAME_SIZE);

  ocpp_frame mmFrame1 =
  {
    .size     = OCPP_CORE_FRAME_SIZE,
    .used_len = 0,
    .remain   = OCPP_CORE_FRAME_SIZE,
  };

  mmFrame1.mem = mWriteMem;

	ocppMakeCallFrame(&mmFrame1, 0, "FW-Tset01", CP_GET_CONFIGURATION, OCPP_CONF);
	//ocpp_frame mmFrame = ocppMakeCallFrame(CALL, "FW-Tset01", CP_BOOT_NOTIFICATION, OCPP_REQ);
	printf("%s: %s\n", __func__, mmFrame1.buf);

    //on_receive_message((void*)test, 72);
    //on_receive_message((void*)test, 93);
}
*/