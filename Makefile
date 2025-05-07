CC := clang
CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-parameter

ifeq ($(MODE),debug)
	CFLAGS += -O0 -g
	BUILD_DIR := build/debug
else
	CLFAGS += -O2 -flto
	BUILD_DIR := build/release
endif

NAME := lox
SOURCES := $(wildcard *.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))

$(BUILD_DIR)/$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ .

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<
