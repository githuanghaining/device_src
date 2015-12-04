#CC=arm-hisiv100nptl-linux-gcc
CC=gcc
AR=ar cr
#CFLAGS=-O0 -Wall -g -shared -fPIC
CFLAGS=-Os -Wall -DOPENSSL -DENABLE_DEBUG -DUSE_OBSOLETE_GETTIMEOFDAY -DENABLE_REPLAY
#LIBS=-lcrypto -lssl -lpthread -lrt
LIBS=
INCLUDE=-I./include


SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
END=libhttpclient.a



TARGET=${OBJ} ${END}

all:${TARGET}


${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@


${END}:${OBJ}
	${AR} ${END} ${OBJ}
	@echo ${OBJ}

clean:
	rm -fr ${TARGET}
	
