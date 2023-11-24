#!/bin/bash

if [ "$1" == "run" ]; then
    # Execute program
    ./prtLife.out
else
    # remove old program
    rm ./prtLife.out
    # Compile program
    compile="gcc main.c \
        particle.c \
        physics.c \
        logger/logger.c \
        display.c \
        vector.c -lGL -lGLU -lglut -lm -o prtLife.out"

    if [ "$1" == "release" ]; then
        $compile -O3 -DLINUX -DVERBOSE_LEVEL=1
    elif [ "$1" == "debug" ]; then
        $compile -O0 -DLINUX -DVERBOSE_LEVEL=3
    else 
        $compile -O0 -DLINUX -DVERBOSE_LEVEL=2
    fi
    # Execute program
    ./prtLife.out
fi