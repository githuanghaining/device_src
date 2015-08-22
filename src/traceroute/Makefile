CC=gcc
AR=ar cr
#CFLAGS=-O0 -Wall -g -shared -fPIC
CFLAGS=-Os -Wall -D_GNU_SOURCE
#LIBS=-lcrypto -lssl -lpthread -lrt
LIBS=
INCLUDE=-I./


SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
END=libtraceroute.a



TARGET=${OBJ} ${END}

all:${TARGET}


${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@


${END}:${OBJ}
	${AR} ${END} ${OBJ}
	@echo ${OBJ}

clean:
	rm -fr ${TARGET}
	
