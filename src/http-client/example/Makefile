#CC=arm-hisiv100nptl-linux-gcc
CC=gcc

CFLAGS=-O0 -Wall -g

INCLUDE=-I../ -I../include
	
LIBS=-L../\
	-Wl,-rpath=../ \
	-lhttpclient \
	-lssl \
	-lcrypto \
	-lpthread \
	-lrt \
	-lm
	
	


SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
BIN=PushTest


TARGET=${OBJ} ${BIN}

all:${TARGET}

${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@

${BIN}:${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LIBS} -o ${BIN}
	@echo ${DEP}
	@echo ${ASS}
	@echo ${OBJ}
#	strip ${BIN}




.PHONY:clean
clean:
	-rm -fr *.o
	-rm -fr ${BIN}
	
