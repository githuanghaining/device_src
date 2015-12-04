PWD     	:= $(shell pwd)
TARGET      	?= arm-arago-linux-gnueabi
CROSS_COMPILE   ?= $(TARGET)-
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
AR      	:= $(CROSS_COMPILE)ar
STRIP		:=$(CROSS_COMPILE)strip
RANLIB      	:= $(CROSS_COMPILE)ranlib
CATEGORY	:= video

INC     	= -I ./include
CFLAGS      	:= -Wall -Os $(EXTRA_CFLAGS) $(INC)
LDFLAGS     	:= $(EXTRA_LDFLAGS) -Wl,--as-needed
LDFLAGS		 += -pthread -L./libs -lTopvdnSDK -L./libs -Wl,-rpath=./libs -lPusher -L./libs -Wl,-rpath=./libs -lNVDSDK -lrt -lm -lstdc++

OPENSSL_SSL_LIB = ./libs/libssl.a
OPENSSL_CRPTO_LIB = ./libs/libcrypto.a
SRV_PUSH_LIB = ./libs/libPusher.so
JPEG_LIB = ./libs/libjpeg.a
#SSL_LIB = ./libs/libpolarssl.a

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
#$(wildcard *.cpp /xxx/xxx/*.cpp) 为获取当前目录下和/xxx/xxx/目录下所有.cpp文件名
#$(patsubst %cpp,%o,$(SRCS)) 为替换所有的cpp为o

INSTALL_DIR=/srv/nfs/nvdsdk
target = LYsdk_main

all: $(target)

#$(target): $(OBJS) $(SRV_PUSH_LIB) $(SSL_LIB)
$(target): $(OBJS)
	$(CPP) $(CFLAGS) -o $(target) $(OBJS) $(LDFLAGS) $(OPENSSL_SSL_LIB) $(OPENSSL_CRPTO_LIB) $(JPEG_LIB) $(SSL_LIB)
	$(STRIP) $(target)
	cp $(target) $(INSTALL_DIR)
	cp $(SRV_PUSH_LIB) $(INSTALL_DIR)/libs

#%.o:%.c
#	$(CPP) $(CFLAGS) -c -o $@ $< 

%.o:%.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<



.PHONY: clean
clean:
	rm -f *.o *.yuv *.bak *.a *.out $(target)

distclean : clean
	rm -f $(targets)
