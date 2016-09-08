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
CFLAGS:=-fPIC

$(TARGET): $(objs)
	@mkdir -p $(BINDIR)
	$(CPP) $(DEBUG) $(INCLUDE) $(objs) -o $(BINDIR)/$(TARGET)
	@chmod 755 $(BINDIR)/$(TARGET)

$(objs): %.o: %.cpp
	$(CPP) $(DEBUG) $(INCLUDE) $(CFLAGS) -c $< -o $@

.PHONY: clean run dump
clean:
	-rm -f $(BINDIR)/$(TARGET) $(SRC)/$(objs)
run:
	$(BINDIR)/$(TARGET)

dump:
	rm -f $(SRC)/$(TARGET).o
	ar rcs libunp.a $(SRC)/*.o
	cp -f libunp.a /home/cmio/projects/third/lib/

