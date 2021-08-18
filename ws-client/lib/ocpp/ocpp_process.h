#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

int on_close(void* in, int len);
int on_write(void* in, int len);
int on_open(void* in, int len);
int on_receive_message(void* in, int len);
int on_send(void* in, int len);
