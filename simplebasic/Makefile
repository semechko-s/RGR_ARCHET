CC=gcc
CFLAGS=-I../mySimpleComputer

OBJ_DIR=.
SOURCES=$(shell find ./* -name '*.c')

OBJECTS=$(SOURCES:./%.c=$(OBJ_DIR)/%.o)
EXECUTABLE=$(OBJ_DIR)/libmSB.a
OBJSLINK := $(wildcard $(OBJ_DIR)/*.o)

all: $(EXECUTABLE) sbt

$(EXECUTABLE): $(OBJECTS)
	ar rcs $@ $^
	ranlib $(EXECUTABLE)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

sbt: $(EXECUTABLE)
	gcc -c main.c -o main.o -I../include -I../mySimpleComputer
	gcc main.o $(OBJSLINK) -o sbt -L$(OBJ_DIR)/ -lmSB
	./sbt fact.sb ../simpleassembler/fact.sa main.o

clean: 
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.a' -exec $(RM) '{}' \;
	rm -f sbt

.PHONY: all sbt clean
