CC := gcc
CP := cp

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
INC_DIR := $(ROOT_DIR)/inc
SRC_DIR := $(ROOT_DIR)/src
OBJ_DIR := $(ROOT_DIR)/obj

SUBDIR_EXCLUDE := circuit

SRC_SUBDIRS := $(filter-out $(SUBDIR_EXCLUDE), $(shell find $(SRC_DIR) -type d -printf "%P "))
OBJ_SUBDIRS := $(addprefix $(OBJ_DIR)/, $(SRC_SUBDIRS))

_SRCS := $(notdir $(wildcard $(SRC_DIR)/*.c)) $(foreach subdir, $(SRC_SUBDIRS), $(addprefix $(subdir)/, $(notdir $(wildcard $(SRC_DIR)/$(subdir)/*.c))))
SRCS := $(addprefix $(SRC_DIR)/, $(_SRCS))
_OBJS := $(foreach src, $(_SRCS), $(patsubst %.c, %.o, $(src)))
OBJS := $(addprefix $(OBJ_DIR)/, $(_OBJS))

LIB_CFLAGS := -ggdb3 -Wall -I$(INC_DIR) -fpic
LIB_LDFLAGS := 

LIB_NAME := libckt.so
LIB := $(ROOT_DIR)/$(LIB_NAME)
LIB_TARGET := /usr/lib/$(LIB_NAME)

lib-all: build-lib
build-lib: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LIB_LDFLAGS) -shared -o $@ $^

lib-obj: $(OBJS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c objdirs
	$(CC) $(LIB_CFLAGS) -o $@ -c $<

objdirs:
ifneq "$(strip $(OBJ_SUBDIRS))" ""
	mkdir -p $(OBJ_SUBDIRS)
endif

install-lib: $(LIB_TARGET)
$(LIB_TARGET): $(LIB)
	$(CP) $< $@
	$(CP) -r $(INC_DIR)/* /usr/local/include/ckt

clean:
	rm -rf $(OBJ_DIR)