//
// Created by Hannah Sheridan on 4/8/23.
//
#include "graphics.h"
#include <stdlib.h>
#include "Wheel.h"

using namespace std;

GLdouble width, height;

int wd;

void initWheel() {

}
void initPlayer() {

}

void init() {
    width = 500;
    height = 500;
    initWheel();
    initPlayer();
}
void initGL() {
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
}

void display() {
    /** Code from Runner GP **/

    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /* Draw here */

    glFlush();
}

void kbd(unsigned int key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}
void kbdS(int key, int x, int y) {
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    /** Code from Runner GP **/

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Wheel of Fortune" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    //glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    //glutTimerFunc(0, cloudTimer, 0);
    //glutTimerFunc(0, buildingTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
