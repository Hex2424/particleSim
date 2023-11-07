/**
 * @file particle.h
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project Iguana and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-07
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdint.h>

typedef float coord_t;
typedef uint32_t color_t;

// Particle as element created here
typedef struct
{
    coord_t x;
    coord_t y;
}Particle_t;

typedef Particle_t* ParticleHandle_t;

// Particle group is set of particles which shares same fate
typedef struct
{
    ParticleHandle_t particlesCloud;
    uint16_t groupSize;
    color_t color;
}ParticlesGroup_t;

typedef ParticlesGroup_t* ParticlesGroupHandle_t;

// Particle cloud is set of Particle groups and overall physic
typedef struct
{
    ParticlesGroupHandle_t particlesCloud;
    uint16_t cloudSize;
    uint16_t currentIdx;
}ParticlesCloud_t;

typedef ParticlesCloud_t* ParticlesCloudHandle_t;

#endif // PARTICLE_H_