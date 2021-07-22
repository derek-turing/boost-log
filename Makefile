# Straight forward Makefile to compile all examples in a row

INCDIR=-I.
LIBS=-lboost_log -lboost_log_setup -lboost_thread -lpthread -lboost_system

COMMONSRC=
#./v4l2_bridge.cpp
        
COMMONHRD=
#./v4l2_bridge.h

# SRC=./avm.c 
SRC=./main.cc

default: all

# Output Name
all: run 

clean:
	rm -f *.o run

run: ${COMMONSRC} ${COMMONHDR} ${SRC}
	g++ ${COMMONSRC} ${SRC} -o $@ ${INCDIR} ${LIBS} -std=c++11 -pedantic -DBOOST_LOG_DYN_LINK
