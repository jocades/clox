#!/usr/bin/env bash

CC=gcc
# CFLAGS="-Wall -Wextra -std=c99"
CFLAGS="-Wall -std=c99"

OUTPUT="a.out"

function build_objects() {
    SOURCES=$(find . -maxdepth 1 -name "*.c")
    OBJECTS=""

    for SRC in $SOURCES; do
        OBJ="${SRC%.c}.o"
        # only compile if the source file is newer than the object file
        if [ ! -f $OBJ ] || [ $SRC -nt $OBJ ]; then
            echo "Compiling $SRC..."
            $CC $CFLAGS -c $SRC -o $OBJ
        fi
        OBJECTS="$OBJECTS $OBJ"
    done

    # link all .o files to create a single executable
    echo "Linking..."
    $GCC $OBJECTS -o $OUTPUT
}

function build() {
    SOURCES=$(find . -maxdepth 1 -name "*.c")
    echo "Compiling..."
    # gcc main.c common.c -o a.out
    $CC -g $CFLAGS $SOURCES -o $OUTPUT

}

RUN_AFTER_BUILD=0
if [ "$1" == "-r" ] || [ $"1" == "--run" ]; then
    RUN_AFTER_BUILD=1
fi

build

if [ $RUN_AFTER_BUILD -eq 1 ]; then
    echo -e "Running $OUTPUT...\n"
    ./$OUTPUT
fi
