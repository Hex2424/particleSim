#include <stdio.h>
#include "particle.h"
#include "config.h"
#include "display.h"

// #define MAX_PARTICLES_COUNT     10

static void jobFunction_(void)
{
    
}

int main(int argc, char **argv)
{
    // Display prepare
    Display_init(argc, argv);

    // Prepare particles cloud
    ParticleCloud_init(5);
    ParticleCloud_addNewGroup(20, RGB(255, 255, 255), Physics_physic(GRAVITY_FORCE, 1));
    ParticleCloud_addNewGroup(20, RGB(255, 0, 255), Physics_physic(GRAVITY_FORCE, 1));
    ParticleCloud_addNewGroup(20, RGB(255, 0, 0), Physics_physic(GRAVITY_FORCE, 1));
   
    Display_startRendering(jobFunction_);

    return 0;
}


