/**
 * @file config.h
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project particleSim and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-08
 */

#ifndef CONFIG_H_
#define CONFIG_H_

    #define WINDOW_NAME             "Particle Life"
    #define WINDOW_POSX             1000
    #define WINDOW_POSY             100

    #define WINDOW_W                500
    #define WINDOW_H                500


    #define ARENA_LEFT_POS          0
    #define ARENA_RIGHT_POS         WINDOW_W
    #define ARENA_BOTTOM_POS        0
    #define ARENA_TOP_POS           WINDOW_H

    #define ARENA_W                 (ARENA_RIGHT_POS - ARENA_LEFT_POS)
    #define ARENA_H                 (ARENA_TOP_POS - ARENA_BOTTOM_POS)

    #define PARTICLE_SIZE           5

    #define VERBOSE_LEVEL           3
    
    #define MAX_ALLOWED_PARTICLES   1000
    #define MAX_ALLOWED_GROUPS      5

    // #if ARENA_X % PARTICLE_SIZE != 0 || ARENA_Y % PARTICLE_SIZE != 0 
    //     #error PARTICLE SIZE IS NOT DIVISABLE PROPERLY
    // #endif

#endif // CONFIG_H_4
