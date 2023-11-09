/**
 * @file display.h
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project Iguana and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-10
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <GL/glut.h>
#include "particle.h"

#define RGB(red, green, blue)   (uint32_t)((((uint8_t)red) << 16) | (((uint8_t)green) << 8) | ((uint8_t)blue << 0))

#define RGB_R(rgb)              (((uint32_t)rgb >> 16) & 0xFF)
#define RGB_G(rgb)              (((uint32_t)rgb >> 8) & 0xFF)
#define RGB_B(rgb)              (((uint32_t)rgb >> 0) & 0xFF)

// Some colors definitions for easier usage

#define RED                     (RGB(255, 0, 0))
#define GREEN                   (RGB(0, 255, 0))
#define BLUE                    (RGB(0, 0, 255))
#define GOLD                    (RGB(255, 215, 0))
#define ORANGE                  (RGB(255, 165,0))
#define PURPLE                  (RGB(138,43,226))

void Display_init(int argc, char **argv);
void Display_startRendering(void (* renderCallback)( void ) );

#endif // DISPLAY_H_