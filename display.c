/**
 * @file display.c
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project Iguana and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-10
 */

#include "display.h"
#include "config.h"

#if LINUX
    #include <unistd.h>
#elif WINDOWS
    #error SLEEP NOT SUPPORTED IN WINDOWS YET
#else
    #error OS NOT DEFINED 
#endif

static void renderScene_(void);

static void (* job)( float deltaTime );

void Display_init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB);    // 1 buffer | enable colors
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glutInitWindowPosition(WINDOW_POSX, WINDOW_POSY);                // window position
    glutInitWindowSize(WINDOW_W, WINDOW_H);           // window size 
    glutCreateWindow(WINDOW_NAME);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glClearColor(0.0, 0.0, 0.0, 0.0);                 // black background
}

void Display_startRendering(void (* jobCallback)( float deltaTime ) )
{
    job = jobCallback;
    glutDisplayFunc(renderScene_);
    glutMainLoop();
}

static void renderScene_(void)
{
    static float delaySeconds = 0;
    static float delaySleep = 0;
    static int oldTimestamp = 0;
    static int currentTimestamp = 0;

    glClear( GL_COLOR_BUFFER_BIT);

    for(ParticlesGroupHandle_t group = ParticleCloud_groupFirst(); group < ParticleCloud_groupLast(); group++)
    {
        // TODO optimize on bytes
        glColor3f(RGB_R(group->colorId), RGB_G(group->colorId), RGB_B(group->colorId));
        // int x = glutGet(GLUT_WINDOW_WIDTH);
        // // int y = glutGet(GLUT_WINDOW_HEIGHT);


        // glPointSize((x * PARTICLE_SIZE) / WINDOW_W);
        glPointSize(PARTICLE_SIZE);
        glBegin(GL_POINTS);

        for(size_t particleIdx = group->particlesBeginPos; particleIdx < group->particlesEndPos; particleIdx++)
        {
            glVertex2s((short) particleCloud.coordsVectors[particleIdx].x, (short) particleCloud.coordsVectors[particleIdx].y);
        }

        glEnd();
    }

    glFlush();
    

    // calling job function
    job(delaySeconds);
    
    currentTimestamp = glutGet(GLUT_ELAPSED_TIME);
    delaySeconds = (currentTimestamp - oldTimestamp) / 1000.0f;
    delaySleep = (1.0f / MAX_FPS_ALLOWED) - delaySeconds;

    if(delaySleep > 0)
    {
        #if LINUX
            usleep(delaySleep * 1000000);
            delaySeconds += delaySleep;
            
        #elif WINDOWS
            // TODO implement in future
        #endif
    }
    
    oldTimestamp = currentTimestamp;
    glutPostRedisplay();

}