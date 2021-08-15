#include <stdio.h>
#include <stdlib.h>

#include "ocpp_process.h"
#include "ocpp_1_6_j.h"

#include "../json/cJSON.h"

static char mMem[512] = {0};

#define CALL       '2'
#define CALLRESULT '3'
#define CALLERROR  '4'

// call        header : [<MessageTypeId>, "<UniqueId>", "<Action>", {<Payload>}]
// call result header : [<MessageTypeId>, "<UniqueId>", {<Payload>}]
// call error  header : [<MessageTypeId>, "<UniqueId>", "<errorCode>", "<errorDescription>", {<errorDetails>}]

void init_frame(ocpp_frame* pFrame, char* pSrc, int pLen, int msgTyep)
{
	if(pLen > sizeof(mMem))
		printf("%s : out of len\n", __func__);

	int i = 0, mmCommaList = 0, mmParantheseList = 0;

	uint8_t mmUniqueIdLen = 0, mmActionLen = 0, mmErrorCodeLen = 0, mmErrorDescLen = 0;

	switch(msgTyep)
	{
		case CALL :
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
		case CALLRESULT :
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
		case CALLERROR :
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
	printf("%s :len(%d)(%s)\n", __func__, j, pId);
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
	printf("%s :len(%d)(%s)\n", __func__, j, pAction);
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
	printf("%s :len(%d)(%s)\n", __func__, j, pErrCode);
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
	printf("%s :len(%d)(%s)\n", __func__, j, pErrDesc);
}


void get_payload(char* pSrc, int pLen, char* pPayload)
{
	int i = 0, j = 0, mmIdLen = 0, mmParantheseList = 0;

	for(i = 0; i <= pLen; i++)
	{
		if(pSrc[i] == '{' || pSrc[i] == ']')
			mmParantheseList++;

		if(mmParantheseList == 1)
		{
			pPayload[j] = pSrc[i];
			j++;
		}
	}

	pPayload[j] = '\0';

	printf("%s :len(%d)(%s)\n", __func__, j, pPayload);
}

int parse_frame(ocpp_frame* pFrame, char* pSrc, int pLen)
{

	//const char CALL = '2', CALLRESULT = '3', CALLERROR = '4';
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
	else
	{
		printf("%s : len check ok!\n", __func__);
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
		case CALL :
		{
			int mmElements = get_elements(pSrc, pLen);
			printf("%s : check msg type (CALL) %d\n", __func__, mmElements);

			if(mmElements != 4)
				printf("%s : invalid elements\n", __func__);

			pFrame->msg_type = CALL;

			get_uniqueId(pSrc, pLen, pFrame->call.uniqueId);
			get_action(pSrc, pLen, pFrame->call.action);
			get_payload(pSrc, pLen, pFrame->call.payload);
		}
		break;
		case CALLRESULT :
		{
			int mmElements = get_elements(pSrc, pLen);
			printf("%s : check msg type (CALLRESULT) %d\n", __func__, mmElements);

			if(mmElements != 3)
				printf("%s : invalid elements\n", __func__);

			pFrame->msg_type = CALLRESULT;

			get_uniqueId(pSrc, pLen, pFrame->callResult.uniqueId);
			//printf("%s : %s\n", __func__, pFrame->callResult.uniqueId);

			get_payload(pSrc, pLen, pFrame->callResult.payload);
			//printf("%s : %s\n", __func__, pFrame->callResult.payload);

		}
		break;
		case CALLERROR :
		{
			int mmElements = get_elements(pSrc, pLen);
			printf("%s : check msg type (CALLERROR) %d\n", __func__, mmElements);

			if(mmElements != 5)
				printf("%s : invalid elements\n", __func__);

			pFrame->msg_type = CALLERROR;
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

int on_receive_message(void* in, int len)
{
	char *mm_buf = (char*)in;

	printf("%s : (%d) %s\r\n",__func__, len, mm_buf);

	ocpp_frame mm_ocpp_frame =
	{
		.size     = 512,
		.used_len = 0,
		.remain   = 512,
	};

	mm_ocpp_frame.mem = mMem;
	parse_frame(&mm_ocpp_frame, mm_buf, len);

}

int on_send(void* in, int len)
{
	printf("%s\n",__func__);
}