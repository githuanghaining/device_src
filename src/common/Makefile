CC=arm-hisiv100nptl-linux-gcc
AR=arm-hisiv100nptl-linux-ar cr
RANLIB=arm-hisiv100nptl-linux-ranlib

INCLUDE =-I../include/
INCLUDE +=-I../rtmp
INCLUDE +=-I../third_lib/libopenssl/install/include/
INCLUDE +=-I../third_lib/libcurl/install/include/
INCLUDE +=-I../http-client

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
	
