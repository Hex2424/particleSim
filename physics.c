/**
 * @file physics.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project particleSim and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-09
 */

#include "physics.h"
#include "particle.h"
#include <math.h>
#include "logger/logger.h"
#include "config.h"

// Physical constants
#define GRAVITY_INCREASE            1000000

const float GRAVITY_CONST = 6.6743E-11 * GRAVITY_INCREASE;


static const char* TAG = "PHYSICS";

inline static void particleReaction_(ParticleHandle_t particleA,
    const PhysicalProperties_t* const particleAProp,
    const ParticleHandle_t const particleB,
    const PhysicalProperties_t* const particleBProp,
    float deltaTime);


PhysicalProperties_t Physics_physic(const EnabledPhysics_t affectingPhysics, const Mass_t mass)
{
    const PhysicalProperties_t physicalProperties = { affectingPhysics, mass };
    return physicalProperties;
}



void Physics_updatePhysics(float deltaTime)
{
    //TODO add delta time in future

    for(ParticlesGroupHandle_t groupA = ParticleCloud_groupFirst(); groupA < ParticleCloud_groupLast(); groupA++)
    {
        for(ParticleHandle_t prtA = groupA->firstParticle; prtA < groupA->lastParticle; prtA++)
        {
            Log_d(TAG, "Start particle Effect %p", prtA);
            for(ParticlesGroupHandle_t groupB = ParticleCloud_groupFirst(); groupB < ParticleCloud_groupLast(); groupB++)
            {
                for(ParticleHandle_t prtB = groupB->firstParticle; prtB < groupB->lastParticle; prtB++)
                {
                    if(prtA != prtB)
                    {
                        particleReaction_(prtA, &groupA->physics, prtB, &groupB->physics, deltaTime);
                    }
                }
            }
            Log_d(TAG, "End particle Effect %p", prtA);

            prtA->originalState = prtA->newState;
        }

    }
}

inline static void particleReaction_(ParticleHandle_t particleA,
    const PhysicalProperties_t* const particleAProp,
    const ParticleHandle_t const particleB,
    const PhysicalProperties_t* const particleBProp,
    float deltaTime)
{
    // TODO add delta time in future
    CoordDirectionVector_t directionVector;
    AccelerationVector_t accelerationVector;
    Log_d(TAG, "delta time:%f", deltaTime);

    directionVector.x = particleB->originalState.x - particleA->originalState.x;
    directionVector.y = particleB->originalState.y - particleA->originalState.y;
    
    float r = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
    float F = (GRAVITY_CONST * particleAProp->mass * particleBProp->mass) / r*r;
    
    float acceleration = F / particleAProp->mass; 

    accelerationVector.ax = directionVector.x / r * acceleration;
    accelerationVector.ay = directionVector.y / r * acceleration;

    particleA->newState.velocity.vx += accelerationVector.ax * deltaTime; // TODO add delta t as time unit not 1
    particleA->newState.velocity.vy += accelerationVector.ay * deltaTime;

    particleA->newState.x += particleA->newState.velocity.vx * deltaTime; // TODO add delta t as time unit not 1
    particleA->newState.y += particleA->newState.velocity.vy * deltaTime;

    if(particleA->newState.x < ARENA_LEFT_POS)
    {
        // X cord smashed to wall :DD
        particleA->newState.x = ARENA_LEFT_POS;
        particleA->newState.velocity.vx = 0;
    }

    if(particleA->newState.x > ARENA_RIGHT_POS)
    {
        // X cord smashed to wall :DD
        particleA->newState.x = ARENA_RIGHT_POS;
        particleA->newState.velocity.vx = 0;
    }

    if(particleA->newState.y < ARENA_BOTTOM_POS)
    {
        // Y cord smashed to RIGHT wall :DD
        particleA->newState.y = ARENA_LEFT_POS;
        particleA->newState.velocity.vy = 0;
    }

    if(particleA->newState.y > ARENA_TOP_POS)
    {
        // Y cord smashed to LEFT wall :DD
        particleA->newState.y = ARENA_RIGHT_POS;
        particleA->newState.velocity.vy = 0;
    }

    if(particleA->newState.x)



    Log_d(TAG, "M1:%u, M2:%u, F:%f, acc:%f, vx:%u, vy:%u, x:%u, y:%u, diffx:%f, diffy:%f", 
        particleAProp->mass, particleBProp->mass,
        F,
        acceleration,
        accelerationVector.ax, accelerationVector.ay,
        particleA->newState.velocity.vx, particleA->newState.velocity.vy,
        particleA->newState.x, particleA->newState.y,
        directionVector.x, directionVector.y);
    

}