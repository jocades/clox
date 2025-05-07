CC := clang
CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-parameter

NAME := lox
BUILD_DIR := build
SOURCES := $(wildcard *.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))

$(BUILD_DIR)/$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<
