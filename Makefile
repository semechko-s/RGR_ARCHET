CC=gcc
CFLAGS= -Wall -Werror -Wextra
LDFLAGS=
OBJ_DIR=obj
SOURCES=$(shell find ./* -name '*.c')

OBJECTS=$(SOURCES:./%.c=$(OBJ_DIR)/%.o)
EXECUTABLE_PR01=./console/pr01
EXECUTABLE_PR02=./console/pr02
EXECUTABLE_PR03=./console/pr03
EXECUTABLE_PR04=./console/pr04


all:
	$(MAKE) -C ./console

clean: 
	$(MAKE) -C ./console clean
	$(RM) $(EXECUTABLE_PR01)
	$(RM) $(EXECUTABLE_PR02)
	$(RM) $(EXECUTABLE_PR03)
	$(RM) $(EXECUTABLE_PR04)
format:
	find . -type f -name '*.[ch]' | xargs clang-format --style GNU -i --verbose

.PHONY: all clean format
