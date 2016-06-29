#!/bin/bash
DIR=../
INCLUDE=-I$(DIR)include
SRC=$(DIR)src
CPP=g++
TARGET:=main
objects:=$(wildcard ./*.o)
objs= unp.o main.o
#all: $(objs)


$(TARGET): $(objs)
	$(CPP) $(objs) -o $(TARGET)
$(objs): %.o: %.cpp
	$(CPP) $(INCLUDE) -c $< -o $@
	@chmod 775 $@

.PHONY: clean
clean:
	echo $(objects)
	rm *.o $(TARGET)
