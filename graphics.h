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
    WHEEL,
    PONG,
    //FLAPPY_START,
    FLAPPY_BIRD,
    FAIL,
    COLORING_BOOK
};

void initWheel();
void initColorBox();
void initPongBars();
void initPongBall();
void initPlayers();

void init();

void initGL();

void drawFromFile(string filename, int x, int y, int pencilSize, color c1, color c2);
void moveBall(int val);
void spinWheel(int val);

void display();

void mouse(int button, int state, int x, int y);

void kbd(unsigned char key, int x, int y);

void kbdS(int key, int x, int y);





#endif //M1OEP_HGSHERID_GRAPHICS_H
