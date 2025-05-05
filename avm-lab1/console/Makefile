CC=gcc
CFLAGS= -Wall -Werror -Wextra
LDFLAGS=
OBJ_DIR=.
SOURCES=$(shell find ./* -name '*.c')

OBJECTS=$(SOURCES:./%.c=$(OBJ_DIR)/%.o)
EXECUTABLE_PR01=pr01
EXECUTABLE_PR02=pr02
EXECUTABLE_PR03=pr03
EXECUTABLE_PR04=pr04


all:  $(EXECUTABLE_PR04) $(OBJECTS)

$(EXECUTABLE_PR04): pr04.o
	gcc pr04.o -L../myReadKey -lmRK -L../myBigChars -lmBC -L../mySimpleComputer -lmSC -L../myTerm -lmT -lm -o pr04

pr04.o: pr04.c lib
	gcc pr04.c -I../include -c -o pr04.o

lib:
	$(MAKE) -C ../mySimpleComputer
	$(MAKE) -C ../myTerm
	$(MAKE) -C ../myBigChars
	$(MAKE) -C ../myReadKey
	$(MAKE) -C ../simplebasic
	$(MAKE) -C ../simpleassembler 

clean: 
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.bin' -exec $(RM) '{}' \;
	$(MAKE) -C ../myBigChars clean
	$(MAKE) -C ../myReadKey clean
	$(MAKE) -C ../mySimpleComputer clean
	$(MAKE) -C ../myTerm clean
	$(MAKE) -C ../simplebasic clean
	$(MAKE) -C ../simpleassembler clean

.PHONY: all clean lib