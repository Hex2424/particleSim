#!/bin/bash

if [ "$1" == "run" ]; then
    # Execute program
    ./prtLife.out
else
    # remove old program
    rm ./prtLife.out
    # Compile program
    if [ "$1" == "release" ]; then
        gcc main.c particle.c physics.c logger/logger.c display.c vector.c -lGL -lGLU -lglut -lm -o prtLife.out -O3
    else
        gcc main.c particle.c physics.c logger/logger.c display.c vector.c -lGL -lGLU -lglut -lm -o prtLife.out -O0
    fi
    # Execute program
    ./prtLife.out
fi