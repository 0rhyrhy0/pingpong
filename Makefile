# Directories
SRC_DIR := src
OBJ_DIR := obj
HEADER_DIR := headers

# File lists
HEADERS := $(wildcard $(HEADER_DIR)/*.h headers.h)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler   
CC := gcc
# add any compiler flags here
CFLAGS := -Wall -Wextra -Werror


# Targets
all: run

main.exe: main.c $(HEADERS) $(OBJS)
	$(CC) -o $@ $< $(OBJS) $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)


.PHONY: run, clean, r

run : main.exe
	@./main.exe

clean:
	rm -rf $(OBJ_DIR)/* main.exe main.exe.stackdump
	
r : 
	make clean
	clear
	@make run --no-print-directory