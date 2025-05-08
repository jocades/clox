CC := clang
CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-parameter

ifeq ($(MODE),debug)
	CFLAGS += -O0 -g -DDEBUG_PRINT_CODE -DDEBUG_TRACE_EXECUTION
	BUILD_DIR := build/debug
else
	CFLAGS += -O2 -flto
	BUILD_DIR := build/release
endif

NAME := lox
BINARY := $(BUILD_DIR)/$(NAME)
SOURCES := $(wildcard *.c)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	cp $@ .

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(BINARY)
	./$(NAME)

test: $(BINARY)
	./test/run

clean:
	rm -rf build

.PHONY: run test clean
