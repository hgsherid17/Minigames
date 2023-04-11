//
// Created by Hannah Sheridan on 4/8/23.
//
#include "graphics.h"
#include <stdlib.h>
#include "circle.h"
#include "shape.h"
#include "quad.h"

using namespace std;

GLdouble width, height;
Circle wheel;
Quad leftBar;
Quad rightBar;
Circle ball;
Quad colorBox;
float rotationAngle = 0.0f;

bool spinning = false;

const color white(1, 1, 1, 1);
const color black(0, 0, 0, 1);
const color dustyRose(0.52, 0.39, 0.39, 1);
const color oldGold(0.81, 0.71, 0.23, 1);
const color seaGreen(0.137255, 0.556863, 0.419608, 1);
const color steelBlue(0.560784, 0.560784, 0.737255, 1);

vector<color> wedgeColors = {dustyRose, oldGold, seaGreen, steelBlue};

int wd;

void initWheel() {
    wheel.setCenter(250, 250);
    wheel.setRadius(200);
    wheel.setColor(0, 0, 0, 1);
}

void initColorBox() {
    colorBox.setCenter(250, 250);
    colorBox.setSize(100, 100);
    colorBox.setColor(seaGreen);
}
/* Pong */
void initPongBars() {
    leftBar.setCenter(20, 250);
    rightBar.setCenter(480, 250);
    leftBar.setColor(white);
    rightBar.setColor(white);
    leftBar.setSize(10, 70);
    rightBar.setSize(10, 70);
}
void initPongBall() {
    ball.setColor(white);
    ball.setCenter(250, 250);
    ball.setRadius(8);
    ball.setVelocity(1, -2);
}

void initPlayers() {

}

void init() {
    width = 500;
    height = 500;
    srand(time(NULL));
    initWheel();
    initPlayers();
    initColorBox();
    initPongBars();
    initPongBall();
}
void initGL() {
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
}
void moveBall(int val) {
    ball.move(ball.getXVelocity(), ball.getYVelocity());
    // Ball hits top
    if (ball.getTopY() < (ball.getRadius() * 2)) {
        ball.bounceY();
        //ball.setCenterY(ball.getRadius());
    }
    // Ball hits bottom
    else if (ball.getBottomY() > height) {
        ball.bounceY();
        //ball.setCenterY(height - ball.getRadius());

    }
    else if (ball.getLeftX() < (ball.getRadius() * 2)) {
        ball.bounceX();
        //ball.setCenterX(ball.getRadius());
    }
    else if (ball.getRightX() > width) {
        ball.bounceX();
        //ball.setCenterX(width - ball.getRadius());
    }

    glutPostRedisplay();
}
void spinWheel(int val) {
    /**
     * TODO: Pass in target index and slow rotation angle as it reaches target
     */
    wheel.spin(rotationAngle);
    rotationAngle += 1.0f;

    if (rotationAngle > 360) {
        rotationAngle -= 360;
    }

    glutPostRedisplay();
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
    if (spinning) {
        glPushMatrix();
        glTranslatef(wheel.getCenterX(), wheel.getCenterY(), 0.0f);
        spinWheel(0);
        glTranslatef(-(wheel.getCenterX()), -(wheel.getCenterY()), 0.0f);
        wheel.drawWedges(12, wedgeColors);
        glPopMatrix();
    }
    else {
        glClearColor(seaGreen.red, seaGreen.green, seaGreen.blue, seaGreen.alpha);
        leftBar.draw();
        rightBar.draw();
        ball.draw();
        moveBall(0);
    }

    glFlush();
}
void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}
void kbd(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 'w') {
        leftBar.moveY(-(height * 0.015));
    }
    if (key == 's') {
        leftBar.moveY(height * 0.015);
    }
    glutPostRedisplay();
}
void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_RIGHT :
            spinning = true;
            break;
        case GLUT_KEY_LEFT :

            break;
        case GLUT_KEY_DOWN :
            rightBar.moveY(height * 0.015);
            break;

        case GLUT_KEY_UP :
            rightBar.moveY(-(height * 0.015));
            break;
    }
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
    glutTimerFunc(25, spinWheel, 0);
    glutTimerFunc(25, moveBall, 0);


    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

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
