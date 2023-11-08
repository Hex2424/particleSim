#include <stdio.h>
#include <GL/glut.h>
#include "particle.h"
#include "config.h"

// #define MAX_PARTICLES_COUNT     10

void proccessParticleGroupDisplay(const ParticlesGroupHandle_t const group)
{
    glColor3f(RGB_R(group->color), RGB_G(group->color), RGB_B(group->color));
    
    glPointSize(5);

    glBegin(GL_POINTS);

    for(ParticleHandle_t prt = group->particles; prt < group->particles + group->groupSize; prt++)
    {
        glVertex3f(prt->x, prt->y, 0.0);
    }

    glEnd();
}


void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT);

    for(ParticlesGroupHandle_t currGroup = ParticleCloud_groupAt(0); currGroup < ParticleCloud_groupAt(ParticleCloud_getGroupsCount()); currGroup++)
    {
        proccessParticleGroupDisplay(currGroup);
    }

    glFlush();
}

int main(int argc, char **argv)
{
    ParticleCloud_init(5);

    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB);  // 1 buffer | enable colors

    glutInitWindowPosition(1000, 100);              // window position
    glutInitWindowSize(ARENA_X, ARENA_Y);           // window size 
    glutCreateWindow ("square");

    glClearColor(0.0, 0, 0, 0.0);                   // black background

    ParticleCloud_addNewGroup(20, RGB(255, 255, 255), Physics_physic(GRAVITY_FORCE, 1));
   
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


