#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char cbuffer[23];

    getTime(cbuffer, 24);

    printf("out: %s\n",cbuffer);

    return 0;
}

