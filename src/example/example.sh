#!/bin/sh
arm-arago-linux-gnueabi-gcc example.c -o example -I./include -pthread -L./libs -lTopvdnSDK -L./libs -Wl,-rpath=./libs -lPusher -L./libs -Wl,-rpath=./libs -lNVDSDK -lrt -lm -lstdc++ ./libs/libssl.a ./libs/libcrypto.a 
