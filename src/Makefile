# Hisilicon Hi3518 sample Makefile

CROSS_COMPILE= arm-arago-linux-gnueabi-
CC:=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar cr
RANLIB=$(CROSS_COMPILE)ranlib
export STRIP:=$(CROSS_COMPILE)strip

export MPP_CFLAGS:= -Wall


# target source
SRC  := $(wildcard ./common/*.o ./storage_push/*.o ./rtmp/*.o ./third_lib/libcurl/curl_static/curl_o/*.o) 
#OBJ  := $(SRC:%.c=%.o)
#SRC =$(wildcard common/*.o)
SUBOBJ =$(shell find ./common/ -name '*.o')
SUBOBJ +=$(shell find ./storage_push/ -name '*.o')
SUBOBJ +=$(shell find ./rtmp/ -name '*.o')
SUBOBJ +=$(shell find ./third_lib/libcurl/curl_static/curl_o/ -name '*.o')


TARGET = libLYSDK.a

${TARGET}:${SUBOBJ}
	${AR} ${TARGET} ${SUBOBJ}
	${RANLIB} ${TARGET}
	mv -f ${TARGET} lib/
	cp -f ./lib/* ./example/libs/
	cp -f ./include/* ./example/include
	@echo ${TARGET}

	 
.PHONY : clean all
clean:
	@rm -f $(TARGET)

