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

// Physical constants
#define GRAVITY_INCREASE            100000

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

    for(ParticlesGroupHandle_t groupA = ParticleCloud_groupAt(0); groupA < ParticleCloud_groupAt(ParticleCloud_getGroupsCount()); groupA++)
    {
        for(ParticleHandle_t prtA = groupA->particles; prtA < groupA->particles + groupA->groupSize; prtA++)
        {
            Log_d(TAG, "Start particle Effect %p", prtA);
            for(ParticlesGroupHandle_t groupB = ParticleCloud_groupAt(0); groupB < ParticleCloud_groupAt(ParticleCloud_getGroupsCount()); groupB++)
            {
                for(ParticleHandle_t prtB = groupB->particles; prtB < groupB->particles + groupB->groupSize; prtB++)
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
    Vector_t directionVector;
    Vector_t accelerationVector;
    Log_d(TAG, "delta time:%f", deltaTime);

    directionVector.a = particleB->originalState.x - particleA->originalState.x;
    directionVector.b = particleB->originalState.y - particleA->originalState.y;

    float r = sqrt(directionVector.a * directionVector.a + directionVector.b * directionVector.b);
    float F = (GRAVITY_CONST * particleAProp->mass * particleBProp->mass) / r*r;
    
    float acceleration = F / particleAProp->mass; 

    accelerationVector.a = directionVector.a / r * acceleration;
    accelerationVector.b = directionVector.b / r * acceleration;

    particleA->newState.velocity.a += accelerationVector.a * deltaTime; // TODO add delta t as time unit not 1
    particleA->newState.velocity.b += accelerationVector.b * deltaTime;

    particleA->newState.x += particleA->newState.velocity.a * deltaTime; // TODO add delta t as time unit not 1
    particleA->newState.y += particleA->newState.velocity.b * deltaTime;

    if(particleA->newState.x < -1)
    {
        // X cord smashed to wall :DD
        particleA->newState.x = -1;
        particleA->newState.velocity.a = 0;
    }

    if(particleA->newState.x > 1)
    {
        // X cord smashed to wall :DD
        particleA->newState.x = 1;
        particleA->newState.velocity.a = 0;
    }

    if(particleA->newState.y < -1)
    {
        // Y cord smashed to RIGHT wall :DD
        particleA->newState.y = -1;
        particleA->newState.velocity.b = 0;
    }

    if(particleA->newState.y > 1)
    {
        // Y cord smashed to LEFT wall :DD
        particleA->newState.y = 1;
        particleA->newState.velocity.b = 0;
    }

    if(particleA->newState.x)



    Log_d(TAG, "M1:%f, M2:%f, F:%f, acc:%f, vx:%f, vy:%f, x:%f, y:%f, diffx:%f, diffy:%f", 
        particleAProp->mass, particleBProp->mass,
        F,
        acceleration,
        accelerationVector.a, accelerationVector.b,
        particleA->newState.velocity.a, particleA->newState.velocity.b,
        particleA->newState.x, particleA->newState.y,
        directionVector.a, directionVector.b);
    

}