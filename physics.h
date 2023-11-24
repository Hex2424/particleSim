/**
 * @file physics.h
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
#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <stdint.h>
#include "vector.h"


typedef uint8_t EnabledPhysics_t;
typedef float Mass_t;

typedef enum
{
    GRAVITY_FORCE = 0x01            // all masks here
}PhysicType_t;

typedef struct
{
    EnabledPhysics_t affectingPhysics;
    Mass_t mass;
}PhysicalProperties_t;


PhysicalProperties_t Physics_physic(const EnabledPhysics_t affectingPhysics, const Mass_t mass);
void Physics_updatePhysics(const float deltaTime);
#endif // PHYSICS_H_