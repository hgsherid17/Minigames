//
// Created by Hannah Sheridan on 4/8/23.
//
#include "graphics.h"
#include <stdlib.h>
#include "circle.h"
#include "shape.h"
#include "quad.h"
#include "oval.h"
#include "cloud.h"
#include <string>
#include <fstream>
#include <memory>

using namespace std;
// Theres a lot going on. my apologies

Game screen = WHEEL;
GLdouble width, height;
Circle wheel;
Circle user;
Oval ov;

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
Quad background;
int bkgHeight;
int bkgWidth;
vector<unique_ptr<Shape>> cat;
vector<unique_ptr<Shape>> dog;


// Flower
Circle recep;
vector<Oval> petals;

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

const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);

const color seaGreen(0.137255, 0.556863, 0.419608, 1);


const color dustyRose(0.52, 0.39, 0.39, 1);
const color oldGold(0.81, 0.71, 0.23, 1);
const color steelBlue(0.560784, 0.560784, 0.737255, 1);

vector<color> wedgeColors = {dustyRose, oldGold, seaGreen, steelBlue};

int wd;

void initWheel() {
    wheel.setCenter((width / 2), (height / 2));
    wheel.setRadius(200);
    wheel.setColor(0, 0, 0, 1);
}

void initColorBox() {
    //background.setBorder(black);
   //background.setColor(white);
    background.setCenter((width / 2) + 25, (height / 2));
    background.setSize(460, 480);

    // Background
    dog.push_back(make_unique<Quad>(background));

    // Tail
    dog.push_back(make_unique<Oval>(white, black, bkgWidth + 110, bkgHeight + 150, 10, 45));
    // Torso
    dog.push_back(make_unique<Oval>(white, black, bkgWidth, bkgHeight + 60, 110, 180));
    // Ears
    dog.push_back(make_unique<Oval>(white, black, bkgWidth - 70, bkgHeight  - 130, 50, 90));
    dog.push_back(make_unique<Oval>(white, black, bkgWidth + 70, bkgHeight  - 130, 50, 90));
    // Paws
    dog.push_back(make_unique<Circle>(white, bkgWidth - 100, bkgHeight + 10, 35));
    dog.push_back(make_unique<Circle>(white, bkgWidth + 100, bkgHeight + 10, 35));
    dog.push_back(make_unique<Circle>(white, bkgWidth - 70, bkgHeight + 205, 35));
    dog.push_back(make_unique<Circle>(white, bkgWidth + 70, bkgHeight + 205, 35));

    // Head
    dog.push_back(make_unique<Circle>(white, bkgWidth, bkgHeight - 130, 85));
    // Eyes
    dog.push_back(make_unique<Circle>(white, bkgWidth - 30, bkgHeight - 150, 10));
    dog.push_back(make_unique<Circle>(white, bkgWidth + 30, bkgHeight - 150, 10));

    // Nose
    dog.push_back(make_unique<Oval>(white, black, bkgWidth, bkgHeight - 120, 20, 10));

    // Init color boxes
    colorBoxes.push_back(Quad(red, 35, 65));
    colorBoxes.push_back(Quad(orange, 35, 125));
    colorBoxes.push_back(Quad(yellow, 35, 185));
    colorBoxes.push_back(Quad(green, 35, 245));
    colorBoxes.push_back(Quad(blue, 35, 305));
    colorBoxes.push_back(Quad(purple, 35, 365));
    colorBoxes.push_back(Quad(black, 35, 425));
    colorBoxes.push_back(Quad(white, 35, 485));

    recep.setRadius(35);
    recep.setColor(white);
    recep.setCenter(30 + (width / 2), height /2);


    ov.setColor(white);
    ov.setBorder(black);
    ov.setRadiusX(20);
    ov.setRadiusY(60);
    ov.setCenter(width/2, height/2);


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
    user.setColor(red);
    user.setBorder(red);
    user.setRadius(6);
}

void init() {
    width = 550;
    height = 550;
    bkgHeight = (height / 2);
    bkgWidth = (width / 2) + 25;
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
void drawFromFile(string filename, int x, int y, int pencilSize, color c1, color c2) {
    ifstream inFile("../" + filename);
    inFile >> noskipws;
    int xCoord = x;
    int yCoord = y;
    char letter;
    bool draw;
    while (inFile >> letter) {
        draw = true;
        switch(letter) {
            case 'w' : glColor3f(c1.red, c1.green, c1.blue); break;
            case ' ': glColor3f(c2.red, c2.green, c2.blue); break; //seaGreen
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
            drawFromFile("winner.txt", width - SCORE_POS_X, height - SCORE_POS_Y, 2, white, seaGreen);
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
            drawFromFile("winner.txt", SCORE_POS_X, height - SCORE_POS_X, 2, white, seaGreen);
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
    switch(screen) {
        case WHEEL :
            glPushMatrix();
            glTranslatef(wheel.getCenterX(), wheel.getCenterY(), 0.0f);
            spinWheel(0);
            glTranslatef(-(wheel.getCenterX()), -(wheel.getCenterY()), 0.0f);
            wheel.drawWedges(12, wedgeColors);
            glPopMatrix();

            break;
        case PONG :
            glClearColor(seaGreen.red, seaGreen.green, seaGreen.blue, seaGreen.alpha);
            leftBar.draw();
            rightBar.draw();
            ball.draw();
            moveBall(0);

            drawFromFile(to_string(leftScore) + ".txt", SCORE_POS_X, SCORE_POS_Y, 10, white, seaGreen);
            drawFromFile(to_string(rightScore)+".txt", width - SCORE_POS_X, SCORE_POS_Y, 10, white, seaGreen);
            break;
        case COLORING_BOOK :
            glClearColor(white.red, white.green, white.blue, white.alpha);
            for (Quad &box : colorBoxes) {
                box.setSize(50, 50);
                box.draw();
            }


            for (const unique_ptr<Shape> &s : dog) {
                if (s == dog[3]) {
                    s->drawRotated(30);
                }
                else if (s == dog[4]) {
                    s->drawRotated(-30);
                }
                else if (s == dog[1]) {
                    s->drawRotated(45);
                }
                else {
                    s->draw();
                }
            }
            drawFromFile("dog.txt", bkgWidth - 47, bkgHeight - 110, 1, black, dog[9]->getColor());

            user.draw();
            break;
        case FLAPPY_BIRD :
            glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, skyBlue.alpha);
            break;

    }

    glFlush();
}
void mouse(int button, int state, int x, int y) {
    bool under = true;

    switch(state) {
        case GLUT_DOWN :
            break;
        case GLUT_UP :
            if (button == GLUT_LEFT_BUTTON) {
                for (Quad box : colorBoxes) {
                    if (user.isOverlapping(box)) {
                        user.setColor(box.getColor());
                        user.setBorder(box.getColor());
                    }
                }
                reverse(dog.begin(), dog.end());
                for (int i = 0; i < dog.size(); i++) {
                    if (dog[i]->isOverlapping(user)) {
                        dog[i]->setColor(user.getColor());
                        i = dog.size();
                    }
                }
                reverse(dog.begin(), dog.end());
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
            screen = PONG;
            spinning = true;
            break;
        case GLUT_KEY_LEFT :
            if (screen == COLORING_BOOK) {
                screen = FLAPPY_BIRD;
            }
            else {
                screen = COLORING_BOOK;
            }
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
    wd = glutCreateWindow("Minigames!" /* title */ );

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
