#include "physics.h"


PhysicalProperties_t Physics_physic(const EnabledPhysics_t affectingPhysics, const Mass_t mass)
{
    const PhysicalProperties_t physicalProperties = { affectingPhysics, mass };
    return physicalProperties;
}