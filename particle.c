/**
 * @file particle.c
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

#include "particle.h"
#include "stdlib.h"
#include "logger/logger.h"
#include "config.h"
#include <string.h>

ParticlesCloud_t particleCloud;

static const char* TAG = "PARTICLE_CLOUD";


void ParticleCloud_init(void)
{   
    // Setting default values as zero
    memset(particleCloud.coordsVectors, 0, MAX_ALLOWED_PARTICLES * sizeof(Coords_t));
    memset(particleCloud.velocityVectors, 0, MAX_ALLOWED_PARTICLES * sizeof(VelocityVector_t));
    memset(particleCloud.accelerationVectors, 0, MAX_ALLOWED_PARTICLES * sizeof(AccelerationVector_t));

    particleCloud.groupStackTop = particleCloud.groupStack;
    particleCloud.particleCurrPosCounter = 0;
}


void ParticleCloud_addNewGroup(const uint16_t particlesCount,
    const color_t colorId,
    const PhysicalProperties_t physics)
{
    ParticlesGroupHandle_t currGroupHandle;

    if(particleCloud.groupStackTop >= (particleCloud.groupStack + MAX_ALLOWED_GROUPS))
    {
        Log_e(TAG, "MAX_ALLOWED_GROUPS : %u EXCEEDED!", MAX_ALLOWED_GROUPS);
        exit(-1);
    }
    
    currGroupHandle = particleCloud.groupStackTop;
    
    currGroupHandle->colorId = colorId;
    currGroupHandle->particlesBeginPos = particleCloud.particleCurrPosCounter;
    currGroupHandle->particlesEndPos= particleCloud.particleCurrPosCounter + particlesCount;
    currGroupHandle->physics = physics;
    
    
    if((particleCloud.particleCurrPosCounter +  particlesCount) >= MAX_ALLOWED_PARTICLES)
    {
        Log_e(TAG, "MAX_ALLOWED_PARTICLES : %u EXCEEDED!", MAX_ALLOWED_PARTICLES);
        exit(-1);
    }

    for(uint32_t particleIdx = currGroupHandle->particlesBeginPos; particleIdx < currGroupHandle->particlesEndPos; particleIdx++)
    {
        Coords_t* currParticleCoords;
        currParticleCoords = &particleCloud.coordsVectors[particleIdx]; 


        currParticleCoords->x = (rand() % ARENA_W + 1) + 1;
        currParticleCoords->y = (rand() % ARENA_H + 1) + 1;    
    }

    particleCloud.groupStackTop++;
    particleCloud.particleCurrPosCounter += particlesCount;
}

ParticlesGroupHandle_t ParticleCloud_groupFirst(void)
{
    return particleCloud.groupStack;
}

ParticlesGroupHandle_t ParticleCloud_groupLast(void)
{
    return particleCloud.groupStackTop;
}