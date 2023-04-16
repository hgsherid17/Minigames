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
#include <unistd.h>


using namespace std;
// Theres a lot going on. my apologies

Game screen = WHEEL;
GLdouble width, height;
Circle user;
Oval ov;
Circle wheel;

Quad pongIcon;
Quad coloringIcon;
Quad flappyIcon;

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

/* Flappy Bird */
vector<Cloud> clouds;
vector<Quad> topPoles;
vector<Quad> bottomPoles;
Circle bird;
bool jumping = false;
Quad start;

Quad grass;

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
const color steelBlue(0.560784, 0.560784, 0.737255, 1);

const vector<color> poleColors = {purple, blue, dustyRose};
vector<color> wedgeColors = {red, orange, yellow, green, blue, purple};

int wd;

void initWheel() {
    int iconHeight = height - 200;
    wheel.setRadius(10);
    wheel.setCenter(width/2, height/2);

    pongIcon.setCenter(width - 100, iconHeight);
    pongIcon.setColor(seaGreen);
    pongIcon.setSize(120, 120);

    coloringIcon.setCenter(width / 2, iconHeight);
    coloringIcon.setColor(red);
    coloringIcon.setSize(120, 120);

    flappyIcon.setCenter(width - (width - 100), iconHeight);
    flappyIcon.setColor(skyBlue);
    flappyIcon.setSize(120, 120);
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
void initFlappyBird() {

    clouds.push_back(Cloud(white, white, 315, 100, 100));
    clouds.push_back(Cloud(white, white,  115, 80, 80));
    clouds.push_back(Cloud(white, white, 465, 50, 60));

    grass.setColor(grassGreen);
    grass.setWidth(width);
    grass.setHeight(height/2);
    grass.setCenter(width/2, height);

    int poleTotal = width + 100;
    int x = width - 100;

    for (const color &c : poleColors) {
        int h = rand() % 300 + 100;
        topPoles.push_back(Quad(c, black, x, 0, 100, h));
        bottomPoles.push_back(Quad(c, black, x, height, 100, poleTotal - h));

        x += 250;
    }

    bird.setCenter(100, height/2);
    bird.setColor(purple);
    bird.setRadius(30);
    bird.setVelocity(0, 0);




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
    initFlappyBird();
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
void fall(int val) {
    bird.setYVelocity(0.81);
    bird.move(bird.getXVelocity(), bird.getYVelocity());

    // Lose if bird goes off screen
    if (bird.getBottomY() >= height) {
        screen = FAIL;
    }

    glutPostRedisplay();



}
void jump(int val) {

    bird.setYVelocity(-15);
    bird.move(bird.getXVelocity(), bird.getYVelocity());




    /*
    chrono::high_resolution_clock clock;
    chrono::time_point<chrono::high_resolution_clock> last, now;
    last = clock.now();
    now = clock.now();
    chrono::duration<double> time = chrono::duration_cast<chrono::duration<double>>(now - last);
    last = now;

    bird.setYVelocity(10);
    //bird.getCenterY() += bird.getYVelocity() * time.count();
    bird.move(bird.getXVelocity(), bird.getYVelocity() * time.count());*/

    glutPostRedisplay();
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
    int x = 0;
    switch(screen) {
        case WHEEL :

            glClearColor(dustyRose.red, dustyRose.green, dustyRose.blue, dustyRose.alpha);
            drawFromFile("welcome.txt", 20, 50, 10, white, dustyRose);

            pongIcon.draw();
            drawFromFile("pong.txt",  width - (pongIcon.getCenterX() /2) + 75,  (height - (pongIcon.getCenterY() / 2)) - 40, 5, white, seaGreen);

            flappyIcon.draw();
            drawFromFile("flappy.txt",  (flappyIcon.getCenterX() /2) - 9,  height - (flappyIcon.getCenterY() / 2) - 50, 4, white, skyBlue);

            coloringIcon.draw();
            drawFromFile("color.txt",  (coloringIcon.getCenterX() /2) + 85,  height - (coloringIcon.getCenterY() / 2) - 35 , 4, white, red);


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
        /*case FLAPPY_START :
            glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, skyBlue.alpha);

            grass.draw();

            for (Cloud &c : clouds) {
                c.draw();
            }

            for (Quad &t : topPoles) {
                t.draw();
            }
            for (Quad &b : bottomPoles) {
                b.draw();
            }

            start.draw();

            drawFromFile("start.txt", width/2, height/2, 5, white, dustyRose);

            wheel.draw();
            break;*/
        case FLAPPY_BIRD :

            glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, skyBlue.alpha);

            grass.draw();

            for (Cloud &c : clouds) {
                c.draw();
            }

            for (Quad &t : topPoles) {
                t.draw();
            }
            for (Quad &b : bottomPoles) {
                b.draw();
            }

            bird.draw();
            fall(0);

            break;

        case FAIL :
            x = width - 100;
            for (int i = 0; i < topPoles.size(); ++i) {
                topPoles[i].setCenterX(x);
                bottomPoles[i].setCenterX(x);

                x += 250;
            }
            string play = "Press the right arrow key to play again";
            string end = "Press the left arrow key to return to menu";
            glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, skyBlue.alpha);
            grass.draw();

            drawFromFile ("start.txt", 100, height/2 - 100, 10, white, skyBlue);

            glRasterPos2i(100, height / 2 + play.length());
            for (const char &letter : play) {
                glColor3f(1, 1, 1);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
            }

            glRasterPos2i(100, height / 2 + 100);
            for (const char &letter : end) {
                glColor3f(1, 1, 1);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
            }
            break;
    }

    glFlush();
}
void mouse(int button, int state, int x, int y) {

    switch(state) {
        case GLUT_DOWN :
            break;
        case GLUT_UP :
            if (button == GLUT_LEFT_BUTTON) {
                if (screen == COLORING_BOOK) {
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

                if (screen == WHEEL) {
                    if (wheel.isOverlapping(pongIcon)) {
                        screen = PONG;
                    }
                    else if (wheel.isOverlapping(coloringIcon)) {
                        screen = COLORING_BOOK;
                    }
                    else if (wheel.isOverlapping(flappyIcon)) {
                        screen = FLAPPY_BIRD;
                    }
                }


            }
            break;
    }
    glutPostRedisplay();
}
void cursor(int x, int y) {
    user.setCenter(x, y);
    wheel.setCenter(x, y);

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
    if (key == 32) {
        jump(0);
       // bird.moveY(-(height * 0.1));
    }
    else {
        //bird.moveY(height * 0.05);
    }
    glutPostRedisplay();
}
void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_RIGHT :
            screen = FLAPPY_BIRD;
            break;
        case GLUT_KEY_LEFT :
            screen = WHEEL;
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
/** From Runner GP **/
void cloudTimer(int dummy) {
    for (Cloud& c : clouds) {
        c.moveLeftAndJumpX(-1, width);
    }

    glutPostRedisplay();
    glutTimerFunc(50, cloudTimer, dummy);
}
void poleTimer(int dummy) {
    for (int i = 0; i < topPoles.size(); ++i) {
        topPoles[i].moveLeftAndJumpX(-3, width);
        bottomPoles[i].moveLeftAndJumpX(-3, width);

        if (topPoles[i].getLeftX() >= width) {
            int h = rand() % 300 + 100;
            int poleTotal = width + 100;
            topPoles[i].setHeight(h);
            bottomPoles[i].setHeight(poleTotal - h);
        }

        if (bird.isOverlapping(topPoles[i]) || bird.isOverlapping(bottomPoles[i])) {
            screen = FAIL;
        }
    }


    glutPostRedisplay();
    glutTimerFunc(30, poleTimer, dummy);
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
    glutTimerFunc(25, fall, 0);
    glutTimerFunc(25, jump, 0);


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
    glutTimerFunc(0, cloudTimer, 0);
    glutTimerFunc(0, poleTimer, 0);
    //glutTimerFunc(0, buildingTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
