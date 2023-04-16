//
// Created by Hannah Sheridan on 4/8/23.
//

#ifndef M1OEP_HGSHERID_GRAPHICS_H
#define M1OEP_HGSHERID_GRAPHICS_H

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
#include "shape.h"
using namespace std;
enum Game {
    START_SCREEN,
    PONG,
    FLAPPY_BIRD,
    FAIL,
    COLORING_BOOK
};

void initStartScreen();
void initColoringBook();
void initPongBall();
void initPong();
void initFlappyBird();

void init();

void initGL();

void drawFromFile(string filename, int x, int y, int pencilSize, color c1, color c2);
void fall(int val);
void jump(int val);
void moveBall(int val);
void spinWheel(int val);

void display();

void mouse(int button, int state, int x, int y);
void cursor(int x, int y);

void kbd(unsigned char key, int x, int y);
void kbdS(int key, int x, int y);

void cloudTimer(int dummy);
void poleTimer(int dummy);



#endif //M1OEP_HGSHERID_GRAPHICS_H
