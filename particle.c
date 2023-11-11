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


bool ParticleCloud_init(const uint16_t maxGroupsInCloud)
{   
    particleCloud.cloudSize = maxGroupsInCloud;
    particleCloud.currentIdx = 0;
    particleCloud.groups = malloc(sizeof(ParticlesGroup_t) * maxGroupsInCloud);

    if(particleCloud.groups == NULL)
    {
        Log_e(TAG, "particleCloud allocation failed of size: %u", maxGroupsInCloud);
        return false;
    }

    return true;
}


bool ParticleCloud_addNewGroup(const uint16_t particlesCount, const color_t color, const PhysicalProperties_t physics)
{
    ParticlesGroupHandle_t currentGroupHandle;

    if(particleCloud.currentIdx >= particleCloud.cloudSize)
    {
        Log_e(TAG, "Cannot add new group to cloud, please increase cloud size, currently:%u", particleCloud.cloudSize);
        return false;
    }

    currentGroupHandle = particleCloud.groups + particleCloud.currentIdx;

    currentGroupHandle->color = color;
    currentGroupHandle->groupSize = particlesCount;
    currentGroupHandle->physics = physics;
    currentGroupHandle->particles = malloc(sizeof(Particle_t) * particlesCount);

    if(currentGroupHandle->particles == NULL)
    {
        Log_e(TAG, "Cannot allocate group: %u with %u particles", particleCloud.currentIdx, particlesCount);
        return false;
    }

    for(ParticleHandle_t currentParticle = currentGroupHandle->particles;
        currentParticle < currentGroupHandle->particles + particlesCount;
        currentParticle++)
    {
        currentParticle->newState.x = (rand() % WINDOW_W) / (WINDOW_W / 2.0f) - 1;
        currentParticle->newState.y = (rand() % WINDOW_H) / (WINDOW_H / 2.0f) - 1;

        currentParticle->originalState = currentParticle->newState;
    }
      

    particleCloud.currentIdx++;

    return true;
}

ParticlesGroupHandle_t ParticleCloud_groupAt(const uint16_t groupIdx)
{
    return particleCloud.groups + groupIdx;
}

uint16_t ParticleCloud_getGroupsCount(void)
{
    return particleCloud.currentIdx;
}