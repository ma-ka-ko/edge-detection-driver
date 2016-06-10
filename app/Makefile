#.PHONY: dot run
ROOT_DIR=..
CC=gcc

CFLAGS=-g

BIN=$(ROOT_DIR)/bin
LIB=$(ROOT_DIR)/lib

EXE_NAME=edge-detector

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

CSRCS = $(wildcard *.c)
COBJS = $(CSRCS:.c=.o)


LIBS += -L$(LIB) 

all: $(BIN)/$(EXE_NAME)  #$(BIN)/EdgeDetector

$(BIN)/$(EXE_NAME): $(BIN) $(COBJS) 
	$(CC) -o $@ $(COBJS) 

$(BIN)/EdgeDetector: $(BIN) $(OBJS) 
	$(CXX) -o $@ $(OBJS) $(LIBS)
	

$(BIN):
	mkdir $(BIN)

#include include.mk

clean::
	@rm -vf $(BIN)/$(EXE_NAME)
	@rm -vf $(BIN)/EdgeDetector
