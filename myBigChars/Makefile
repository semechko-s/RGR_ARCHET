CC=gcc
LDFLAGS=
OBJ_DIR=./
SOURCES=$(shell find ./* -name '*.c')

OBJECTS=$(SOURCES:./%.c=$(OBJ_DIR)/%.o)
EXECUTABLE=$(OBJ_DIR)/libmBC.a


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	ar rcs $@ $^
	ranlib $(EXECUTABLE)

$(OBJ_DIR)/%.o: %.c
	$(CC) -I../include -c $(CFLAGS) $< -o $@


clean: 
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.a' -exec $(RM) '{}' \;

.PHONY: all clean