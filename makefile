#!/bin/bash
DIR=.
INCLUDE=-I$(DIR)/include
SRC=$(DIR)/src
CPP=g++
DEBUG=-g
BINDIR:=$(DIR)/bin
TARGET:=main
sources:=$(wildcard $(SRC)/*.cpp)
#objects:=$(subset $(SRC)/, $(BINDIR)/, $(sources))
objs:=$(sources:.cpp=.o)

$(TARGET): $(objs)
	@mkdir -p $(BINDIR)
	$(CPP) $(DEBUG) $(objs) -o $(BINDIR)/$(TARGET)
	@chmod 755 $(BINDIR)/$(TARGET)
$(objs): %.o: %.cpp
	$(CPP) $(DEBUG) $(INCLUDE) -c $< -o $@

.PHONY: clean run
clean:
	-rm -f $(BINDIR)/$(TARGET) $(SRC)/$(objs)
run:
	$(BINDIR)/$(TARGET)
