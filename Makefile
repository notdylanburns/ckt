CC := gcc

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

SRC := $(ROOT_DIR)/ckt.c
OBJ := $(ROOT_DIR)/ckt.o

LIB_DIR := $(ROOT_DIR)/libckt

CFLAGS := -Wall
LDFLAGS := -lckt

TARGET := $(ROOT_DIR)/ckt

all: build clean
build: $(TARGET) 
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $^

obj: $(OBJ)
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ)

.PHONY: all