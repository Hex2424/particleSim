/**
 * @file particle.h
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project particleSim and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-07
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdint.h>
#include <stdbool.h>
#include "physics.h"
#include "config.h"

typedef struct
{
    float x;
    float y;
}Coords_t;

typedef uint32_t color_t;

// #define BITS_UINT32 (sizeof(uint32_t) * __CHAR_BIT__)

// Particle group is set of particles which shares same fate
typedef struct
{
    uint32_t particlesBeginPos;
    uint32_t particlesEndPos;
    color_t colorId;
    PhysicalProperties_t physics;
}ParticlesGroup_t;

typedef ParticlesGroup_t* ParticlesGroupHandle_t;

// Particle cloud is set of Particle groups and overall physic
typedef struct
{
    ParticlesGroup_t groupStack[MAX_ALLOWED_GROUPS];
    ParticlesGroupHandle_t groupStackTop;

    uint32_t particleCurrPosCounter;
    AccelerationVector_t accelerationVectors[MAX_ALLOWED_PARTICLES];  // like a acceleration matrix
    VelocityVector_t velocityVectors[MAX_ALLOWED_PARTICLES];          // like a velocity matrix
    Coords_t coordsVectors[MAX_ALLOWED_PARTICLES];                    // like a x, y position matrix

}ParticlesCloud_t;

typedef ParticlesCloud_t* ParticlesCloudHandle_t;
extern ParticlesCloud_t particleCloud;


void ParticleCloud_init(void);
void ParticleCloud_addNewGroup(const uint16_t particlesCount, const color_t color, const PhysicalProperties_t physics);
ParticlesGroupHandle_t ParticleCloud_groupLast(void);
ParticlesGroupHandle_t ParticleCloud_groupFirst(void);
#endif // PARTICLE_H_