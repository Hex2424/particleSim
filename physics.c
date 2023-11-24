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

inline static void updateAccelerationVectors_(void);
inline static void updateVelocityVectors_(const float deltaTime);
inline static void updateCoordsVectors_(const float deltaTime);


PhysicalProperties_t Physics_physic(const EnabledPhysics_t affectingPhysics, const Mass_t mass)
{
    const PhysicalProperties_t physicalProperties = { affectingPhysics, mass };
    return physicalProperties;
}



void Physics_updatePhysics(const float deltaTime)
{
    // Calculating new accelerations
    updateAccelerationVectors_();

    // Calculating new Velocities
    updateVelocityVectors_(deltaTime);

    // Calculating new Coordinates
    updateCoordsVectors_(deltaTime);
}



inline static void updateAccelerationVectors_(void)
{
    // Now calculating particles reactions with other particles without including itselfs and already calculated connections
    for(ParticlesGroupHandle_t groupA = ParticleCloud_groupFirst(); groupA < ParticleCloud_groupLast(); groupA++)
    {
        ParticlesGroupHandle_t currentBGroup = groupA;
        // Groups:    {    }{ }
        // Particles: [1, 2, 3]
        //             |__|  |
        //             |_____|
        //                |__|
        // Avoiding repeats using this algorithm
        for(uint32_t prtIdxA = groupA->particlesBeginPos; prtIdxA < groupA->particlesEndPos; prtIdxA++)
        {
            for(uint32_t prtIdxB = (prtIdxA + 1); prtIdxB < particleCloud.particleCurrPosCounter; prtIdxB++)
            {
                CoordDirectionVector_t directionVectorA;
                const Coords_t* prtACoords = &particleCloud.coordsVectors[prtIdxA];
                const Coords_t* prtBCoords = &particleCloud.coordsVectors[prtIdxB];
                const Mass_t massA = groupA->physics.mass;
                Mass_t massB;

                if(currentBGroup->particlesEndPos == prtIdxB)
                {
                    // Detecting currentB group change
                    currentBGroup++;
                }

                massB = currentBGroup->physics.mass;              

                // Direction for particleA, *-1 this we would get particleB direction vector
                directionVectorA.x = prtBCoords->x - prtACoords->x;
                directionVectorA.y = prtBCoords->y - prtACoords->y;
                
                float r = sqrt(directionVectorA.x * directionVectorA.x + directionVectorA.y * directionVectorA.y);
                
                if(r == 0.0f)
                {
                    r = 0.001;
                }


                float F = (GRAVITY_CONST * massA * massB) / r*r;
            
                float accelerationA = F / massA;
                float accelerationB = F / massB; 

                // TODO later on we need sum acceleration vectors from differend physics
                // Updating both particles accelerations
                particleCloud.accelerationVectors[prtIdxA].ax = (directionVectorA.x / r) * accelerationA;
                particleCloud.accelerationVectors[prtIdxA].ay = (directionVectorA.y / r) * accelerationA;

                particleCloud.accelerationVectors[prtIdxB].ax = (-directionVectorA.x / r) * accelerationB;
                particleCloud.accelerationVectors[prtIdxB].ay = (-directionVectorA.y / r) * accelerationB;

            }
        }
    }
}

inline static void updateVelocityVectors_(const float deltaTime)
{
    for(uint32_t prtIdx = 0; prtIdx < particleCloud.particleCurrPosCounter; prtIdx++)
    {
        // v = a * t
        // curr_v = new_v + old_v
        particleCloud.velocityVectors[prtIdx].vx += particleCloud.accelerationVectors[prtIdx].ax * deltaTime;
        particleCloud.velocityVectors[prtIdx].vy += particleCloud.accelerationVectors[prtIdx].ay * deltaTime;
    }
}

inline static void updateCoordsVectors_(const float deltaTime)
{
    Coords_t* coords;
    VelocityVector_t* velocity; 

    for(uint32_t prtIdx = 0; prtIdx < particleCloud.particleCurrPosCounter; prtIdx++)
    {
        // s = v * t
        // curr_s = new_s + old_s
        coords = &particleCloud.coordsVectors[prtIdx];
        velocity = &particleCloud.velocityVectors[prtIdx];
        
        coords->x += velocity->vx * deltaTime;
        coords->y += velocity->vy * deltaTime;

        if(coords->x < ARENA_LEFT_POS)
        {
            // X cord smashed to wall :DD
            coords->x = ARENA_LEFT_POS;
            velocity->vx = 0;
        }

        if(coords->x > ARENA_RIGHT_POS)
        {
            // X cord smashed to wall :DD
            coords->x = ARENA_RIGHT_POS;
            velocity->vx = 0;
        }

        if(coords->y < ARENA_BOTTOM_POS)
        {
            // Y cord smashed to RIGHT wall :DD
            coords->y = ARENA_LEFT_POS;
            velocity->vy = 0;
        }

        if(coords->y > ARENA_TOP_POS)
        {
            // Y cord smashed to LEFT wall :DD
            coords->y = ARENA_RIGHT_POS;
            velocity->vy = 0;
        }

    }
    // Log_d(TAG, "M1:%u, M2:%u, F:%f, acc:%f, vx:%u, vy:%u, x:%u, y:%u, diffx:%f, diffy:%f", 
    //     particleAProp->mass, particleBProp->mass,
    //     F,
    //     acceleration,
    //     accelerationVector.ax, accelerationVector.ay,
    //     particleA->newState.velocity.vx, particleA->newState.velocity.vy,
    //     particleA->newState.x, particleA->newState.y,
    //     directionVector.x, directionVector.y);
}