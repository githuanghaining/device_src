################################################################
# File:				Makefile
# Author:			weil
# Date:				9/12/2015
# Organization:		Topvdn Inc.
# Copyright (c) ...
# All rights reserved.
################################################################

################################################################
# host
ifeq ($(CROSS),)
	CROSS = arm-arago-linux-gnueabi-
	#CROSS = arm-hisiv100nptl-linux-
endif
CC = $(CROSS)gcc
AR = $(CROSS)ar crs
RANLIB = $(CROSS)ranlib
STRIP = $(STRIP)strip

################################################################
# target directory
TARGET_DIR = lib
# target binary
TARGET_STATIC := $(TARGET_DIR)/libTopvdnSDK.a
TARGET_SHARED := $(TARGET_DIR)/libTopvdnSDK.so

# target sources
#SRCDIRLIST := common rtmp storage_push
SRCDIRLIST := common_test rtmp_test http-client
C_SOURCES := $(foreach SUBDIR,$(SRCDIRLIST),$(wildcard $(SUBDIR)/*.c))

# ignored sources
_SOURCES := 

# filter out
C_SOURCES := $(filter-out $(_SOURCES),$(C_SOURCES))

################################################################
# compile objects' directories
OBJDIR := .objs
OBJDIRLIST := $(foreach SUBDIR,$(SRCDIRLIST),$(OBJDIR)/$(SUBDIR))
OBJDIRLIST += $(TARGET_DIR)

################################################################
# .o
C_OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(C_SOURCES))
# .o.d
DEPS := $(addsuffix .d,$(C_OBJS))

################################################################
# includes added here
INCLUDES := -Iinclude \
			-Icommon_test \
			-Irtmp_test \
			-Ihttp-client/include \
			-Ihttp-client
INCLUDES += -Ithird_lib/libcurl/install/include/
INCLUDES += -Ithird_lib/libopenssl/install/include/
				
################################################################
# defines added here
DEFINES := -D_GNU_SOURCE -D_REENTRANT

################################################################
# compile flags
CFLAGS += $(DEFINES) $(INCLUDES) -W -Wall -Wno-psabi -fomit-frame-pointer -Os -pthread -DOPENSSL

################################################################
# link flags
LDFLAGS	+= -Wl,-rpath=.

################################################################
# paths to search depended libs
LDFLAGS += -Llib -Lthird_lib/libcurl/install/lib

################################################################
# link libs
LDLIBS := -lPusher -pthread
#LDLIBS := -lPusher -lcurl -lssl -lcrypto -pthread

################################################################
# extra objs
EXTRA_OBJS := $(wildcard third_lib/libcurl/curl_static/curl_o/*.o)

################################################################
# post build shell command
POST_BUILD := cp -f ${TARGET_STATIC} ./example/libs/
#POST_BUILD += cp -f ./include/* ./example/include


.PHONY:all clean

all:$(OBJDIRLIST) $(TARGET_SHARED) $(TARGET_STATIC)

$(TARGET_SHARED):$(C_OBJS)
	$(CC) -shared -fPIC -o $@ $^ $(LDFLAGS) $(LDLIBS)
	#cp -f $(TARGET_SHARED) ./example/libs/
	#$(POST_BUILD)

$(TARGET_STATIC):$(C_OBJS)
	#@echo "$(AR) $@ $^ <extra objs...>";$(AR) $@ $^
	@echo "$(AR) $@ $^ <extra objs...>";$(AR) $@ $^ $(EXTRA_OBJS)
	$(POST_BUILD)
	cp -f ./include/* ./example/include
	cp -f ./lib/libPusher.so ./example/libs/

$(C_OBJS):$(OBJDIR)/%.o:%.c
	$(CC) $(CFLAGS) -c -Wp,-MMD,$@.d.tmp -o $@ $<
	@echo -n $(dir $@) >$@.d;cat $@.d.tmp >>$@.d;$(RM) $@.d.tmp

$(DEPS):
	@if test -f $(basename $@);then echo Missing $@;$(RM) $(basename $@);fi

-include $(DEPS)

$(OBJDIRLIST):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(TARGET_SHARED) $(TARGET_STATIC)
