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
        compile2="$compile -O3 -DLINUX -DVERBOSE_LEVEL=1"
    elif [ "$1" == "debug" ]; then
        compile2="$compile -O0 -DLINUX -DVERBOSE_LEVEL=3"
    else
        compile2="$compile -O0 -DLINUX -DVERBOSE_LEVEL=2"
    fi

    if [ "$2" == "profile" ]; then
        $compile2 -DENABLED_PROFILE -g -pg
    else
        $compile2
    fi

    if [ "$2" == "profile" ]; then
        gprof -l ./prtLife.out gmon.out > analysis.txt
    else
        # Execute program
        ./prtLife.out
    fi

fi