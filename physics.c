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
#include <time.h>
#include <string.h>
#include "vectorizedTables.h"
#include <stdlib.h>
// Physical constants
#define GRAVITY_INCREASE            1E11

const float GRAVITY_CONST = 6.6743E-11 * GRAVITY_INCREASE;
// const float GRAVITY_CONST = 1;

static const char* TAG = "PHYSICS";

inline static void updateAccelerationVectors_(void);
inline static void updateVelocityVectors_(const float deltaTime);
inline static void updateCoordsVectors_(const float deltaTime);
inline static bool isCollision_(const Coords_t const* coordsA, const Coords_t const * coordsB);

PhysicalProperties_t Physics_physic(const EnabledPhysics_t affectingPhysics, const Mass_t mass)
{
    const PhysicalProperties_t physicalProperties = { affectingPhysics, mass };
    return physicalProperties;
}



void Physics_updatePhysics(const float deltaTime)
{

    clock_t start, end;
    unsigned long cpu_time_used;
    
    // Acceleration matrix must be resetted each time since its not assign happening but accelerations sum
    memset(particleCloud.accelerationVectors, 0, particleCloud.particleCurrPosCounter * sizeof(AccelerationVector_t));
    start = clock();

    // Calculating new accelerations
    updateAccelerationVectors_();
    
    end = clock();
    cpu_time_used = ((end - start));
    printf("aclock: %lo\n", cpu_time_used);

    // start = clock();
    // Calculating new Velocities
    updateVelocityVectors_(deltaTime);
    // end = clock();
    // cpu_time_used = ((end - start));
    // printf("vclock: %lo\n", cpu_time_used);

    // start = clock();
    // Calculating new Coordinates
    updateCoordsVectors_(deltaTime);
    // end = clock();
    // cpu_time_used = ((end - start));
    // printf("cclock: %lo\n", cpu_time_used);


}
inline static void updateAccelerationVectors_(void)
{
    
    // Now calculating particles reactions with other particles without including itselfs and already calculated connections
    for(ParticlesGroupHandle_t groupA = particleCloud.groupStack; groupA < particleCloud.groupStackTop; groupA++)
    {
        ParticlesGroupHandle_t currentBGroup = groupA;
        // Groups:    {    }{ }
        // Particles: [1, 2, 3]
        //             |__|  |
        //             |_____|
        //                |__|
        // Avoiding repeats using this algorithm
        #pragma omp parallel for collapse(2) if(particleCloud.particleCurrPosCounter > 5000)
        for(uint32_t prtIdxA = groupA->particlesBeginPos; prtIdxA < groupA->particlesEndPos; prtIdxA++)
        {
            for(uint32_t prtIdxB = (prtIdxA + 1); prtIdxB < particleCloud.particleCurrPosCounter; prtIdxB++)
            {
                Coords_t directionVectorA;
                const Mass_t massA = groupA->physics.mass;

                
                if(currentBGroup->particlesEndPos == prtIdxB)
                {
                    // Detecting currentB group change
                    currentBGroup++;
                }

                const Mass_t massB = currentBGroup->physics.mass;              

                // // Direction for particleA, *-1 this we would get particleB direction vector
                directionVectorA.x = particleCloud.coordsVectors[prtIdxB].x - particleCloud.coordsVectors[prtIdxA].x;
                directionVectorA.y = particleCloud.coordsVectors[prtIdxB].y - particleCloud.coordsVectors[prtIdxA].y;

                uint16_t xPos = (uint16_t)fabs(directionVectorA.x);
                uint16_t yPos = (uint16_t)fabs(directionVectorA.y);

                float fvaluex = xyDivR3LookupTable[xPos][yPos];
                float fvaluey = xyDivR3LookupTable[yPos][xPos];

                
                if (directionVectorA.x < 0)
                {
                    particleCloud.accelerationVectors[prtIdxA].ax -= fvaluex * massB;
                    particleCloud.accelerationVectors[prtIdxB].ax += fvaluex * massA;
                }else
                {
                    particleCloud.accelerationVectors[prtIdxA].ax += fvaluex * massB;
                    particleCloud.accelerationVectors[prtIdxB].ax -= fvaluex * massA;
                }
            

        
                if (directionVectorA.y < 0)
                {
                    particleCloud.accelerationVectors[prtIdxA].ay -= fvaluey * massB;
                    particleCloud.accelerationVectors[prtIdxB].ay += fvaluey * massA;
                }else
                {
                    particleCloud.accelerationVectors[prtIdxA].ay += fvaluey * massB;
                    particleCloud.accelerationVectors[prtIdxB].ay -= fvaluey * massA;
                }
            
  

                            // end = clock();
                // cpu_time_used = ((end - start));
                // printf("iterclock: %lo\n", cpu_time_used);
                // Log_d(TAG, "M1:%f, M2:%f, F:%f, accA:%f, accB:%f", 
                //     massA, massB,F,accelerationA, accelerationB);
            }
        } 
    }
} //305225
  //3771120

inline static void updateVelocityVectors_(const float deltaTime)
{
    for(uint32_t prtIdx = 0; prtIdx < particleCloud.particleCurrPosCounter; prtIdx++)
    {
        // v = a * t
        // curr_v = new_v + old_v
        particleCloud.velocityVectors[prtIdx].vx += particleCloud.accelerationVectors[prtIdx].ax * GRAVITY_CONST * deltaTime;
        particleCloud.velocityVectors[prtIdx].vy += particleCloud.accelerationVectors[prtIdx].ay * GRAVITY_CONST * deltaTime;
    }
}

inline static void updateCoordsVectors_(const float deltaTime)
{
    Coords_t* coordsA;
    Coords_t* coordsB;
    VelocityVector_t* velocityA; 
    VelocityVector_t* velocityB;

    for(uint32_t prtIdx = 0; prtIdx < particleCloud.particleCurrPosCounter; prtIdx++)
    {
        // s = v * t
        // curr_s = new_s + old_s
        coordsA = &particleCloud.coordsVectors[prtIdx];
        velocityA = &particleCloud.velocityVectors[prtIdx];
        
        // for(uint32_t prtIdx2 = (prtIdx + 1); prtIdx2 < particleCloud.particleCurrPosCounter; prtIdx2++)
        // {
        //     coordsB = &particleCloud.coordsVectors[prtIdx];
        //     velocityB = &particleCloud.velocityVectors[prtIdx];
      
        //     if(isCollision_(coordsA, coordsB))
        //     {
        //         velocityA->vx = 0;
        //         velocityA->vy = 0;
        //         break;
        //     }

        //     coordsB->x += velocityB->vx * deltaTime;
        //     coordsB->y += velocityB->vy * deltaTime;
        // }

        coordsA->x += velocityA->vx * deltaTime;
        coordsA->y += velocityA->vy * deltaTime;

        if(coordsA->x < ARENA_LEFT_POS)
        {
            // X cord smashed to wall :DD
            coordsA->x = ARENA_LEFT_POS;
            velocityA->vx = 0;
        }

        if(coordsA->x > ARENA_RIGHT_POS)
        {
            // X cord smashed to wall :DD
            coordsA->x = ARENA_RIGHT_POS;
            velocityA->vx = 0;
        }

        if(coordsA->y < ARENA_BOTTOM_POS)
        {
            // Y cord smashed to RIGHT wall :DD
            coordsA->y = ARENA_LEFT_POS;
            velocityA->vy = 0;
        }

        if(coordsA->y > ARENA_TOP_POS)
        {
            // Y cord smashed to LEFT wall :DD
            coordsA->y = ARENA_RIGHT_POS;
            velocityA->vy = 0;
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

inline static bool isCollision_(const Coords_t* coordsA, const Coords_t* coordsB) {
    bool xCollide = false;
    bool yCollide = false;

    if ((coordsA->x + (PARTICLE_SIZE / 2)) > (coordsB->x - (PARTICLE_SIZE / 2)) &&
        (coordsA->x - (PARTICLE_SIZE / 2)) < (coordsB->x + (PARTICLE_SIZE / 2))) {
        xCollide = true;
    }

    if ((coordsA->y + (PARTICLE_SIZE / 2)) > (coordsB->y - (PARTICLE_SIZE / 2)) &&
        (coordsA->y - (PARTICLE_SIZE / 2)) < (coordsB->y + (PARTICLE_SIZE / 2))) {
        yCollide = true;
    }

    return (xCollide && yCollide);
}