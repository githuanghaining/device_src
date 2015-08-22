CC=arm-hisiv100nptl-linux-gcc

CFLAGS=-O2 -Wall

INCLUDE=-I../
	
LIBS=-L../ -lntpclient -lrt
	
SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
BIN=ntpclient


TARGET=${OBJ} ${BIN}

all:${TARGET}

${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@

${BIN}:${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LIBS} -o ${BIN}
	@echo ${OBJ}




.PHONY:clean
clean:
	-rm -fr *.o
	-rm -fr ${BIN}
