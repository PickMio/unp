#!/bin/bash
DIR=.
INCLUDE=-I$(DIR)/include
SRC=$(DIR)/src
CPP=g++
BINDIR:=$(DIR)/bin
TARGET:=main
sources:=$(wildcard $(SRC)/*.cpp)
#objects:=$(subset $(SRC)/, $(BINDIR)/, $(sources))
objs:=$(sources:.cpp=.o)

$(TARGET): $(objs)
	@mkdir -p $(BINDIR)
	$(CPP) $(objs) -o $(BINDIR)/$(TARGET)
	@chmod 755 $(BINDIR)/$(TARGET)
$(objs): %.o: %.cpp
	$(CPP) $(INCLUDE) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(BINDIR)/$(TARGET) $(SRC)/$(objs)
.PHONY: run
run:
	$(BINDIR)/$(TARGET)
