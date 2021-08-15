#include <stdio.h>
#include <stdlib.h>
#include "../json/cJSON.h"
#include "ocpp_process.h"

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

	ocpp_parse_frame(mm_buf, len);

}

int on_send(void* in, int len)
{
	printf("%s\n",__func__);
}