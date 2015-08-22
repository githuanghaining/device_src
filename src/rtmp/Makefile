CC=arm-arago-linux-gnueabi-gcc
AR=arm-arago-linux-gnueabi-ar cr
RANLIB=arm-arago-linux-gnueabi-ranlib
#CFLAGS=-O0 -Wall -g -shared -fPIC
CFLAGS=-O0 -Wall
#LIBS=-lcrypto -lssl -lpthread -lrt
LIBS=
#INCLUDE=-I../../../../../middleware/openssl/middleware/include/
INCLUDE=-I../common


SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
END=librtmpclient.a



TARGET=${OBJ} ${END}

all:${TARGET}


${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@


${END}:${OBJ}
	${AR} ${END} ${OBJ}
	${RANLIB} ${END}
#	cp -f ${END} ../lib
	@echo ${OBJ}

clean:
	rm -fr ${TARGET}
	
