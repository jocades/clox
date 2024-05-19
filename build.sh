#!/usr/bin/env bash

CC=gcc
CFLAGS="-g -Wall -Wextra -std=c99"
OUTPUT="a.out"

build() {
    SOURCES=$(find . -maxdepth 1 -name "*.c")
    CMD="$CC $CFLAGS $SOURCES -o $OUTPUT"
    echo $CMD
    echo "Compiling..."
    $CMD
}

RUN_AFTER_BUILD=0
if [ "$1" == "-r" ] || [ $"1" == "--run" ]; then
    RUN_AFTER_BUILD=1
fi

build

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
else
    echo "Compilation successful."
fi

if [ $RUN_AFTER_BUILD -eq 1 ]; then
    echo -e "Running $OUTPUT...\n"
    ./$OUTPUT
fi
