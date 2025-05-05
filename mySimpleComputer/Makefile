CC=gcc

LDFLAGS=
OBJ_DIR=.
SOURCES=$(shell find ./* -name '*.c')

OBJECTS=$(SOURCES:./%.c=$(OBJ_DIR)/%.o)
EXECUTABLE=$(OBJ_DIR)/libmSC.a


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	ar rcs $@ $^
	ranlib $(EXECUTABLE)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


clean: 
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

.PHONY: all clean