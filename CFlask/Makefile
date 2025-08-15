PROG = flask
SRC = flask.c

TOP = ../..
CIVETWEB_LIB = libcivetweb.a

CFLAGS = -I$(TOP)/include $(COPT)
LIBS = -lpthread

include $(TOP)/resources/Makefile.in-os

ifeq ($(TARGET_OS),LINUX) 
	LIBS += -ldl
endif

all: $(PROG)

$(PROG): $(CIVETWEB_LIB) $(SRC) functions.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(CIVETWEB_LIB) $(LIBS) functions.o

functions.o: functions.h functionslist.h functions.c
	$(CC) -c functions.c functions.h functionslist.h

$(CIVETWEB_LIB):
	$(MAKE) -C $(TOP) clean lib
	cp $(TOP)/$(CIVETWEB_LIB) .

clean:
	rm -f $(CIVETWEB_LIB) $(PROG) functions.o 

.PHONY: all clean
