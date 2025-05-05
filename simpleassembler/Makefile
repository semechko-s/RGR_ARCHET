CC=gcc
CFLAGS=-I../mySimpleComputer -lmSC

OBJ_DIR=.
SOURCES=$(shell find ./* -name '*.c')

OBJECTS=$(SOURCES:./%.c=$(OBJ_DIR)/%.o)
EXECUTABLE=$(OBJ_DIR)/libmSA.a
OBJSLINK := $(wildcard $(OBJ_DIR)/*.o)

all: $(EXECUTABLE) sat

$(EXECUTABLE): $(OBJECTS)
	ar rcs $@ $^
	ranlib $(EXECUTABLE)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

sat: $(EXECUTABLE)
	gcc main.c -I../include -c -o main.o
	gcc main.o -L../mySimpleComputer -lmSC -o sat -L$(OBJ_DIR)/ -lmSA 
	./sat fact.sa main.o

clean: 
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.a' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.sa' -exec $(RM) '{}' \;
	rm -f sat

.PHONY: all sat clean

