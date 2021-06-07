
ROOT_DIR = $(shell pwd)

ifeq ($(TARGET_ARCH),)
	CXX = arm-linux-gnueabihf-g++
	CC = arm-linux-gnueabihf-gcc
else ifeq ($(TARGET_ARCH),x86)
	CXX = g++
	CC = gcc
endif

LINK = ar

#工程名称
RROJECT_NAME = mytest
battery_dir = ./battery

vpath %.c    $(ROOT_DIR)
vpath %.cpp  $(ROOT_DIR)
vpath %.h    $(ROOT_DIR)
vpath %.hpp  $(ROOT_DIR)
vpath %.S    $(ROOT_DIR)
vpath %.asm  $(ROOT_DIR)


#debug文件夹里的makefile文件需要最后执行，所以这里需要执行的子目录�?�排�?debug文件夹，这里使用awk排除了debug文件夹，读取剩下的文件夹
#SUBDIRS=E:\mycode\test_armcc\main

EXCLUDE_DIR := -path ./build \
			-o -path ./json* \
			-o -path ./.vscode \
			-o -path ./.git* \
			-o -path ./osdk-core/linker/armv8 \
			-o -path ./osdk-core/linker/STM32 \
			

ifeq ($(TARGET_ARCH),)
	EXCLUDE_DIR += -o -path ./osdk-core/linker/x86 
else ifeq ($(TARGET_ARCH),x86)
	EXCLUDE_DIR += -o -path ./osdk-core/linker/armv7 
endif

SUBDIRS= $(shell find ./ -maxdepth 6  \( $(EXCLUDE_DIR)\) -prune -o -type d -print)

CSCR_DIR = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.c))
CSCR_DIR := $(sort $(CSCR_DIR))

CXXSCR_DIR = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.cpp))

# CSCR_FILE = $(notdir $(CSCR_DIR))
# CXXSCR_FILE = $(notdir $(CXXSCR_DIR))

CSCR_FILE = $(CSCR_DIR)
CXXSCR_FILE = $(CXXSCR_DIR)


# ifndef release
# 	Bulid = $(ROOT_DIR)/build/debug
# 	$(shell mkdir $(Bulid))
# else
# 	Bulid = $(ROOT_DIR)/build/release
# 	$(shell mkdir $(Bulid))
# endif


#获取所有头文件�?�?
HPP_FILE = $(shell find ./ -name *.hpp)
HPP_FILE += $(shell find ./ -name *.h)

#将文件名去除
INCLUDE_DIR_ALL =$(foreach dir, $(HPP_FILE),$(patsubst %/$(notdir $(dir)),%,$(dir)))
INCLUDE_DIR_ALL += /home/lan/comdin/Dji_SDK/lib/libusb-1.0.24/usbtest/include \
				   
				   

INCLUDE_DIR = $(sort $(INCLUDE_DIR_ALL))

LIB_DIR = osdk-core/linker/x86/lib/libdji-linker.a \
		  /home/lan/comdin/Dji_SDK/lib/libusb-1.0.24/libusb/.libs/libusb-1.0.a \
		  /usr/local/lib/libavcodec.a \
		  /usr/local/lib/libavformat.a \
		  /usr/local/lib/libavutil.a \
		  /home/lan/comdin/Dji_SDK/lib/FFmpeg-n4.4/libswresample/libswresample.a \
		  /usr/local/lib/libswscale.a -lz  osdk-core/linker/x86/lib/libdji-linker.a /usr/local/lib/libavcodec.a /usr/local/lib/libavformat.a /usr/local/lib/libavutil.a /home/lan/comdin/Dji_SDK/lib/FFmpeg-n4.4/libswresample/libswresample.a /usr/local/lib/libswscale.a -lz -lpthread

#INCLUDE_DIR = -I $(shell chdir)

OBJS_DIR=build/Objects

BIN_DIR=$(Bulid)\bin

CUR_SOURCE=${wildcard *.c}

ifeq ($(TARGET_ARCH),x86)
	battery_make = cd $(battery_dir) & make -f $(battery_dir)/Makefile_bak
else
	battery_make = make -C $(battery_dir)
endif


C_OBJS=${patsubst ./%.c,$(OBJS_DIR)/%.o, $(CSCR_FILE)}
CXX_OBJS=${patsubst ./%.cpp, $(OBJS_DIR)/%.o, $(CXXSCR_FILE)}


INCLUDE_DIR := $(patsubst %, -I %, $(INCLUDE_DIR))


#SDK中需要使用的宏定义
CXX_DEFINES = -DADVANCED_SENSING -DDJIOSDK_HARDWARE_TYPE=3 -DDJIOSDK_IS_DEBUG=1 -DDJIOSDK_MAJOR_VERSION=4 -DDJIOSDK_MINOR_VERSION=1 -DDJIOSDK_OPERATOR_TYPE=1 -DDJIOSDK_PATCH_VERSION=0 -DPLATFORM_OSDK -DWAYPT2_CORE

#将以下变量�?�出到子shell�?，本次相当于导出到子�?录下的makefile�?
export CC CXX BIN OBJS_DIR BIN_DIR ROOT_DIR INCLUDE_DIR FROM_ELF_FLAG LINK_FLAG ASMCOMPILE_FLAG CCOMPILE_FLAG ASMC FROM_ELF LINK RROJECT_NAME
export INCLUDE_DIR CXX_DEFINES


$(info -------------------------------)
ifeq ($(TARGET_ARCH),)
$(info build for arm)
else 
$(info build for x86_64)
endif
$(info start compile )
$(info -------------------------------)
#注意这里的顺序，需要先执�?�SUBDIRS最后才能是DEBUGs
all:$(C_OBJS) $(CXX_OBJS) battery_sample h264

#将c文件编译为o文件，并放在指定放置�?标文件的�?录中即OBJS_DIR
$(OBJS_DIR)/%.o:%.c
	@mkdir -p $(patsubst %/$(notdir $@),%, $@)
	@echo CC $(notdir $<) 
	@$(CC) -c -g -O0  -std=c99 -D_GNU_SOURCE $(CXX_DEFINES)  $< $(INCLUDE_DIR) -o $@ 
$(OBJS_DIR)/%.o:%.cpp
	@echo CXX $(notdir $<) 
	@mkdir -p $(patsubst %/$(notdir $@),%, $@)
#	$(CXX)  -M  -std=c++11 $(CXX_DEFINES) $< $(INCLUDE_DIR)  -o $(OBJS_DIR)/$@ 
	@$(CXX)  -c -g -O0 -std=c++11 -pthread -g -fPIC -g $(CXX_DEFINES) $< $(INCLUDE_DIR)  -o $@ 
# $(CUR_SCOBJS):%.o:%.s
# 	$(ASMC)  -c -O2 $(INCLUDE_DIR) $< -o $(OBJS_DIR)/$@ 

h264:
	make -C camera_h264_callback_sample

battery_sample:
	$(battery_make)

clean:
	rm -rf $(ROOT_DIR)/build/*
	$(battery_make) clean
	make -C camera_h264_callback_sample clean

PHONY +=battery clean h264

.PHONY: PHONY