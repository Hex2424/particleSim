#!/bin/bash

if [ "$1" == "run" ]; then
    # Execute program
    ./prtLife.out
else
    # remove old program
    rm ./prtLife.out
    # Compile program
    gcc main.c particle.c physics.c logger/logger.c display.c -lGL -lGLU -lglut -lm -o prtLife.out
    # Execute program
    ./prtLife.out
fi