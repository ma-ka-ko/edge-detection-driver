#.PHONY: dot run
ROOT_DIR=..
BIN=$(ROOT_DIR)/bin
LIB=$(ROOT_DIR)/lib

EXE_NAME=edgei-detector

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

LIBS += -L$(LIB) 

all: $(BIN)/$(EXE_NAME)

$(BIN)/$(EXE_NAME): $(OBJS) 
	$(CXX) -o $@ $(OBJS) $(LIBS)

include include.mk

clean::
	@rm -vf $(BIN)/$(EXE_NAME)
