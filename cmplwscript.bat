gcc main.c particle.c physics.c logger/logger.c display.c vector.c  -DWINDOWS -o prtLife.exe -O3 -std=c99 -lm -lopengl32 -lglu32 -L. -lfreeglut