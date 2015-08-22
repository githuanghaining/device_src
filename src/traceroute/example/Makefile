C=gcc

CFLAGS=-Os -g -Wall -D_GNU_SOURCE

INCLUDE=-I../
	
LIBS=-L../ -ltraceroute -lm
	
	


SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(SOURCE))
BIN=trace_test


TARGET=${DEP} ${ASS} ${OBJ} ${BIN}

all:${TARGET}

${OBJ}:%.o:%.c
	${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@

${BIN}:${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LIBS} -o ${BIN}
	@echo ${OBJ}




.PHONY:clean
clean:
	-rm -fr *.d
	-rm -fr *.s
	-rm -fr *.o
	-rm -fr ${BIN}
