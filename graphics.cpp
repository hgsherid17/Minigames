//
// Created by Hannah Sheridan on 4/8/23.
//
#include "graphics.h"
#include <stdlib.h>
#include "circle.h"
#include "shape.h"
#include "quad.h"
#include <string>
#include <fstream>

using namespace std;

GLdouble width, height;
Circle wheel;
Circle user;

/* Pong */
Quad leftBar;
Quad rightBar;
Circle ball;
int leftScore;
int rightScore;
bool leftWinner = false;
bool rightWinner = false;
const int SCORE_POS_X = 100;
const int SCORE_POS_Y = 50;

/* Coloring Book */
vector<Quad> colorBoxes;
vector<Circle> circles;

float rotationAngle = 0.0f;

bool spinning = false;

const color white(1, 1, 1, 1);
const color black(0, 0, 0, 1);
const color red(1, 0, 0, 1);
const color orange(1, 0.5, 0, 1);
const color yellow(1, 1, 0, 1);
const color green(0, 1, 0, 1);
const color blue(0, 0, 1, 0);
const color purple(0.5, 0, 1, 1);
const color dustyRose(0.52, 0.39, 0.39, 1);
const color oldGold(0.81, 0.71, 0.23, 1);
const color seaGreen(0.137255, 0.556863, 0.419608, 1);
const color steelBlue(0.560784, 0.560784, 0.737255, 1);

vector<color> wedgeColors = {dustyRose, oldGold, seaGreen, steelBlue};

int wd;

void initWheel() {
    wheel.setCenter((width / 2), (height / 2));
    wheel.setRadius(200);
    wheel.setColor(0, 0, 0, 1);
}

void initColorBox() {
    colorBoxes.push_back(Quad(red, 30, 60));
    colorBoxes.push_back(Quad(orange, 30, 120));
    colorBoxes.push_back(Quad(yellow, 30, 180));
    colorBoxes.push_back(Quad(green, 30, 240));
    colorBoxes.push_back(Quad(blue, 30, 300));
    colorBoxes.push_back(Quad(purple, 30, 360));
    colorBoxes.push_back(Quad(black, 30, 420));
    colorBoxes.push_back(Quad(white, 30, 480));

    for (int i = 100; i <= 500; i += 100){
        circles.push_back(Circle(white, 300, i, 20));
    }
}
/* Pong */
void initPongBars() {
    leftBar.setCenter(20, (height / 2));
    rightBar.setCenter((width - 20), (height / 2));
    leftBar.setColor(white);
    rightBar.setColor(white);
    leftBar.setSize(10, 70);
    rightBar.setSize(10, 70);

    leftScore = 0;
    rightScore = 0;
}
void initPongBall() {
    ball.setColor(white);
    ball.setCenter((width / 2), (height / 2));
    ball.setRadius(8);
    ball.setVelocity(rand() % 2 == 0 ? 1 : -1, rand() % 2 == 0 ? 1 : -1);
}

void initPlayers() {
    user.setColor(white);
    user.setRadius(10);
}

void init() {
    width = 550;
    height = 550;
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
void showPongScore(string filename, int x, int y, int pencilSize) {
    ifstream inFile("../" + filename);
    inFile >> noskipws;
    int xCoord = x;
    int yCoord = y;
    char letter;
    bool draw;
    while (inFile >> letter) {
        draw = true;
        switch(letter) {
            case 'w' : glColor3f(1, 1, 1); break;
            case ' ': glColor3f(0.137255, 0.556863, 0.419608); break; //seaGreen
            default: // newline
                draw = false;
                xCoord = x;
                yCoord += pencilSize;
        }
        if (draw) {
            glBegin(GL_QUADS);
            glVertex2i(xCoord, yCoord);
            glVertex2i(xCoord+pencilSize, yCoord);
            glVertex2i(xCoord+pencilSize, yCoord+pencilSize);
            glVertex2i(xCoord, yCoord+pencilSize);
            glEnd();
            xCoord += pencilSize;
        }
    }
    inFile.close();
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
        //ball.bounceX();
        initPongBall();
        //ball.setCenter(250, 250);
        ++rightScore;
        if (rightScore == 2) {
            showPongScore("winner.txt", width - SCORE_POS_X, height - SCORE_POS_Y, 2);
            leftScore = 0;
            rightScore = 0;
        }
        //ball.setCenterX(ball.getRadius());
    }
    else if (ball.getRightX() > width) {
        initPongBall();
        //ball.setCenter(250, 250);
        //ball.bounceX();
        ++leftScore;
        if (leftScore == 2) {
            showPongScore("winner.txt", SCORE_POS_X, height - SCORE_POS_X, 2);
            leftScore = 0;
            rightScore = 0;
        }
        //ball.setCenterX(width - ball.getRadius());
    }
    if (ball.isColliding(leftBar) || ball.isColliding(rightBar)) {
        ball.bounceX();
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
        glClearColor(white.red, white.green, white.blue, white.alpha);
        for (Quad &box : colorBoxes) {
            box.setSize(50, 50);
            box.draw();
        }

        for (Circle &circ : circles) {
            circ.draw();
        }

        user.draw();
       /* glClearColor(seaGreen.red, seaGreen.green, seaGreen.blue, seaGreen.alpha);
        leftBar.draw();
        rightBar.draw();
        ball.draw();
        moveBall(0);

        showPongScore(to_string(leftScore) + ".txt", SCORE_POS_X, SCORE_POS_Y, 10);
        showPongScore(to_string(rightScore)+".txt", width - SCORE_POS_X, SCORE_POS_Y, 10);
    */
    }

    glFlush();
}
void mouse(int button, int state, int x, int y) {

    switch(state) {
        case GLUT_DOWN :
            break;
        case GLUT_UP :
            if (button == GLUT_LEFT_BUTTON) {
                for (Quad box : colorBoxes) {
                    if (user.isOverlapping(box)) {
                        user.setColor(box.getColor());
                    }
                }
                for (Circle circ : circles) {
                    if (user.isOverlapping(circ)) {
                        circ.setColor(user.getColor());
                    }
                }
            }
            break;
    }
    glutPostRedisplay();
}
void cursor(int x, int y) {
    user.setCenter(x, y);

    glutPostRedisplay();
}
void kbd(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 'w') {
        if (leftBar.getTopY() != 20) {
            leftBar.moveY(-(height * 0.05));
        }

    }
    if (key == 's') {
        if (leftBar.getBottomY() != height) {
            leftBar.moveY(height * 0.05);
        }
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
            if (rightBar.getBottomY() != height) {
                rightBar.moveY(height * 0.05);
            }
            break;

        case GLUT_KEY_UP :
            if (rightBar.getTopY() != 0) {
                rightBar.moveY(-(height * 0.05));
            }

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
    glutPassiveMotionFunc(cursor);

    // handles timer
    //glutTimerFunc(0, cloudTimer, 0);
    //glutTimerFunc(0, buildingTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
