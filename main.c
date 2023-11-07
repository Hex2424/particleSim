#include <stdio.h>
#include <GL/glut.h>
#include "particle.h"

#define ARENA_X                 500
#define ARENA_Y                 500

// #define MAX_PARTICLES_COUNT     10

static ParticlesGroup_t particleGroups[] = {{10, 10, 50}, {20, 20, 50}};

static uint16_t currentParticlesCount = 2;

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    
    glPointSize(5);

    glBegin(GL_POINTS);

    for(uint16_t prtIdx = 0; prtIdx < currentParticlesCount; prtIdx++)
    {
        glVertex3f(particles[prtIdx].x, particles[prtIdx].y, 0.0);
    }

    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{

    
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB); // 1 buffer | enable colors

    glutInitWindowPosition(1000, 100);      // window position
    glutInitWindowSize(600, 600);           // window size 
    glutCreateWindow ("square");

    glClearColor(0.0, 0, 0, 0.0);               // black background
    glMatrixMode(GL_PROJECTION);                // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, ARENA_X, 0.0, ARENA_Y, 0.0, 1.0);   // setup a 10x10x2 viewing world


   
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


