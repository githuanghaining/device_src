CC=arm-arago-linux-gnueabi-gcc
AR=arm-arago-linux-gnueabi-ar cr
RANLIB=arm-arago-linux-gnueabi-ranlib
CFLAGS=-O2 -Wall
CFLAGS += -std=c99 -W -Wall -Wpointer-arith -Wcast-align -Wcast-qual -Wshadow -Waggregate-return -Wnested-externs -Winline -Wwrite-strings -Wstrict-prototypes
CFLAGS += -DENABLE_DEBUG -DUSE_OBSOLETE_GETTIMEOFDAY -DENABLE_REPLAY
LIBS=
INCLUDE=


SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
END=libntpclient.a



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
	
