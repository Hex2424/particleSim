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

typedef float coord_t;
typedef float color_t;

typedef struct
{
    coord_t x;
    coord_t y;
    Vector_t velocity;
}ParticleState_t;

// Particle as element created here
typedef struct
{
    // To prevent calculations after state change
    ParticleState_t originalState;
    ParticleState_t newState;
}Particle_t;

typedef Particle_t* ParticleHandle_t;

// Particle group is set of particles which shares same fate
typedef struct
{
    ParticleHandle_t firstParticle;
    ParticleHandle_t lastParticle;
    color_t color;
    PhysicalProperties_t physics;
}ParticlesGroup_t;

typedef ParticlesGroup_t* ParticlesGroupHandle_t;

// Particle cloud is set of Particle groups and overall physic
typedef struct
{
    Particle_t particleStack[MAX_ALLOWED_PARTICLES];
    ParticlesGroup_t groupStack[MAX_ALLOWED_GROUPS];

    ParticleHandle_t particleStackTop;
    ParticlesGroupHandle_t groupStackTop;

}ParticlesCloud_t;

typedef ParticlesCloud_t* ParticlesCloudHandle_t;

void ParticleCloud_init(void);
bool ParticleCloud_addNewGroup(const uint16_t particlesCount, const color_t color, const PhysicalProperties_t physics);
ParticlesGroupHandle_t ParticleCloud_groupLast(void);
ParticlesGroupHandle_t ParticleCloud_groupFirst(void);
#endif // PARTICLE_H_