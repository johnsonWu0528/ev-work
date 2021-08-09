# MakeFile for ws-client

CC = arm-linux-gnueabi-gcc
LIBS = -lpthread -lwebsockets
OCPP_VER_1.6_SRC = lib/ocpp/ocpp_1_6_j.c
OCPP_VER_1.6_OBJ = lib/ocpp/ocpp_1_6_j.o
cJSON_SRC = lib/json/cJSON.c
cJSON_OBJ = lib/json/cJSON.o
APP_SRC = src/noodoe_client.c
APP_EXE = app/noodoe_client

CLEAN_OBJS= ${OCPP_VER_1.6_OBJ} ${cJSON_OBJ} ${APP_EXE}

main :
	$(CC) -c ${OCPP_VER_1.6_SRC} -o ${OCPP_VER_1.6_OBJ}
	$(CC) -c ${cJSON_SRC} -o ${cJSON_OBJ}
	$(CC) -o ${APP_EXE} ${APP_SRC} ${OCPP_VER_1.6_OBJ} ${cJSON_OBJ} ${LIBS}

clean :
	rm -rf ${CLEAN_OBJS}
