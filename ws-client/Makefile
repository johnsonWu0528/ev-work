# MakeFile for ws-client

CC = arm-linux-gnueabi-gcc
#CC = gcc

LIBS = -lpthread -lwebsockets
OCPP_VER_1.6_SRC = lib/ocpp/ocpp_1_6_j.c
OCPP_VER_1.6_OBJ = lib/ocpp/ocpp_1_6_j.o
OCPP_PROCESS_SRC = lib/ocpp/ocpp_process.c
OCPP_PROCESS_OBJ = lib/ocpp/ocpp_process.o

cJSON_SRC = lib/json/cJSON.c
cJSON_OBJ = lib/json/cJSON.o

APP_SRC = src/noodoe_client.c
APP_EXE = app/noodoe_client

#APP_SRC = lib/ocpp/ocpp_process.c
#APP_EXE = lib/ocpp/ocpp_process

INSTALL_PATH = /home/johnson/work/qemu/rootfs/media

CLEAN_OBJS= ${OCPP_VER_1.6_OBJ} ${OCPP_PROCESS_OBJ} ${cJSON_OBJ} ${APP_EXE}

main :
	@echo 'build noodoe client'

	@$(CC) -c ${OCPP_VER_1.6_SRC} -o ${OCPP_VER_1.6_OBJ}
	@echo 'file 1 : '${OCPP_VER_1.6_SRC} ${OCPP_VER_1.6_OBJ}

	@$(CC) -c ${OCPP_PROCESS_SRC} -o ${OCPP_PROCESS_OBJ}
	@echo 'file 2 : '${OCPP_PROCESS_SRC} ${OCPP_PROCESS_OBJ}

	@$(CC) -c ${cJSON_SRC} -o ${cJSON_OBJ}
	@echo 'file 3 : '${cJSON_SRC} ${cJSON_OBJ}

	@$(CC) -o ${APP_EXE} ${APP_SRC} ${OCPP_VER_1.6_OBJ} ${OCPP_PROCESS_OBJ} ${cJSON_OBJ} ${LIBS}
	@echo 'build success'

	@#$(CC) -c ${OCPP_VER_1.6_SRC} -o ${OCPP_VER_1.6_OBJ}
	@#$(CC) -c ${cJSON_SRC} -o ${cJSON_OBJ}
	@#$(CC) -o ${APP_EXE} ${APP_SRC} ${OCPP_VER_1.6_OBJ} ${cJSON_OBJ}

clean :
	rm -rf ${CLEAN_OBJS}

install :
	sudo cp ${APP_EXE} ${INSTALL_PATH}

all:
	rm -rf ${CLEAN_OBJS}

	@echo ''
	@echo 'build noodoe client'


	@$(CC) -c ${OCPP_VER_1.6_SRC} -o ${OCPP_VER_1.6_OBJ}
	@echo 'file 1 : '${OCPP_VER_1.6_SRC} ${OCPP_VER_1.6_OBJ}

	@$(CC) -c ${OCPP_PROCESS_SRC} -o ${OCPP_PROCESS_OBJ}
	@echo 'file 2 : '${OCPP_PROCESS_SRC} ${OCPP_PROCESS_OBJ}

	@$(CC) -c ${cJSON_SRC} -o ${cJSON_OBJ}
	@echo 'file 3 : '${cJSON_SRC} ${cJSON_OBJ}

	@$(CC) -o ${APP_EXE} ${APP_SRC} ${OCPP_VER_1.6_OBJ} ${OCPP_PROCESS_OBJ} ${cJSON_OBJ} ${LIBS}
	@echo 'build success'
	@echo ''

	sudo cp ${APP_EXE} ${INSTALL_PATH}
