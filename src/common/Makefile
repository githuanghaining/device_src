CC=arm-arago-linux-gnueabi-gcc
AR=arm-arago-linux-gnueabi-ar cr
RANLIB=arm-arago-linux-gnueabi-ranlib

INCLUDE =-I../include/
INCLUDE +=-I../rtmp
INCLUDE +=-I../third_lib/libopenssl/install/include/
INCLUDE +=-I../third_lib/libcurl/install/include/

#CFLAGS=-O0 -Wall -g -shared -fPIC
CFLAGS=-O0 -Wall $(INCLUDE)
#LIBS=-lcrypto -lssl -lpthread -lrt
LIBS=

SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
END=libcommon.a



TARGET=${OBJ} ${END}

all:${TARGET}


${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} $< -o $@


${END}:${OBJ}
	${AR} ${END} ${OBJ}
	${RANLIB} ${END}
#	cp -f ${END} ../lib
	@echo ${OBJ}

clean:
	rm -fr ${TARGET}
	
