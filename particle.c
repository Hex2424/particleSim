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

static ParticlesCloud_t particleCloud;

static const char* TAG = "PARTICLE_CLOUD";


void ParticleCloud_init(void)
{   
    particleCloud.particleStackTop = particleCloud.particleStack;
    particleCloud.groupStackTop = particleCloud.groupStack;
}


bool ParticleCloud_addNewGroup(const uint16_t particlesCount, const color_t color, const PhysicalProperties_t physics)
{
    ParticlesGroupHandle_t currentGroupHandle;

    if(particleCloud.groupStackTop >= (particleCloud.groupStack + MAX_ALLOWED_GROUPS))
    {
        Log_e(TAG, "MAX_ALLOWED_GROUPS : %u EXCEEDED!", MAX_ALLOWED_GROUPS);
        return false;
    }
    
    currentGroupHandle = particleCloud.groupStackTop;

    currentGroupHandle->color = color;
    currentGroupHandle->firstParticle = particleCloud.particleStackTop;
    currentGroupHandle->lastParticle = currentGroupHandle->firstParticle + particlesCount;
    currentGroupHandle->physics = physics;
    
    if(currentGroupHandle->lastParticle >= (particleCloud.particleStack + MAX_ALLOWED_PARTICLES))
    {
        Log_e(TAG, "MAX_ALLOWED_PARTICLES : %u EXCEEDED!", MAX_ALLOWED_PARTICLES);
        return false;
    }

    for( ; particleCloud.particleStackTop < currentGroupHandle->lastParticle; particleCloud.particleStackTop++)
    {
        ParticleHandle_t particle;
        particle = particleCloud.particleStackTop;

        particle->newState.x = (rand() % ARENA_W + 1) + 1;
        particle->newState.y = (rand() % ARENA_H + 1) + 1;
        
        particle->newState.velocity.vx = 0;
        particle->newState.velocity.vy = 0;

        particle->originalState = particle->newState;
    }

   
    particleCloud.groupStackTop++;
    
    return true;
}

ParticlesGroupHandle_t ParticleCloud_groupFirst(void)
{
    return particleCloud.groupStack;
}

ParticlesGroupHandle_t ParticleCloud_groupLast(void)
{
    return particleCloud.groupStackTop;
}

