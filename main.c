#include <stdio.h>
#include "particle.h"
#include "config.h"
#include "display.h"
#include "physics.h"

// #define MAX_PARTICLES_COUNT     10

static void jobFunction_(float deltaTime)
{
    Physics_updatePhysics(deltaTime);
}

int main(int argc, char **argv)
{
    // Display prepare
    Display_init(argc, argv);

    // Prepare particles cloud
    ParticleCloud_init();
    ParticleCloud_addNewGroup(3, WHITE, Physics_physic(GRAVITY_FORCE, 100000));

    ParticleCloud_addNewGroup(1, RED, Physics_physic(GRAVITY_FORCE, 1));
    // ParticleCloud_addNewGroup(100, GREEN, Physics_physic(GRAVITY_FORCE, 1000));
    // ParticleCloud_addNewGroup(10, ORANGE, Physics_physic(GRAVITY_FORCE, 10000));

    // Simulate(WHITE, RED, GRAVITY_FORCE);
    // Simulate(WHITE, RED, GRAVITY_ATTRACTION);

    // ParticleCloud_addNewGroup(10, BLUE, Physics_physic(GRAVITY_FORCE, 100));
    // ParticleCloud_addNewGroup(1, BLUE, Physics_physic(GRAVITY_FORCE, 1));
    // ParticleCloud_addNewGroup(20, RGB(255, 0, 0), Physics_physic(GRAVITY_FORCE, 100000));
   
    Display_startRendering(jobFunction_);

    return 0;
}