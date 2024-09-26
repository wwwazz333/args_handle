# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Ilib -fPIC
CFLAGS_DEBUG = -Wall -Wextra -Ilib -fPIC -g -DDEBUG
LIB_SRC = lib/handle_args.c
OBJ_DIR = obj
MAIN_SRC = main.c
MAIN_OBJ = main
LIB_OBJ = handle_args.o
STATIC_LIB = libhandle_args.a
DYNAMIC_LIB = libhandle_args.so

# Default target
all: static dynamic

# command "install" to install the library on linux
install: dynamic
	cp $(DYNAMIC_LIB) /usr/lib
	cp lib/handle_args.h /usr/include

# Compile object file
$(LIB_OBJ): $(LIB_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(LIB_OBJ) $(MAIN_SRC)
	$(CC) $(CFLAGS) $^ -o $@

debug: $(LIB_SRC) $(MAIN_SRC)
	$(CC) $(CFLAGS_DEBUG) $^ -o $(MAIN_OBJ)

# Create static library
static: $(LIB_OBJ)
	ar rcs $(STATIC_LIB) $(LIB_OBJ)

# Create dynamic library
dynamic: $(LIB_OBJ)
	$(CC) -shared -o $(DYNAMIC_LIB) $(LIB_OBJ)

# Clean up
clean:
	rm -f $(LIB_OBJ) $(MAIN_OBJ) $(STATIC_LIB) $(DYNAMIC_LIB)

.PHONY: all static dynamic clean