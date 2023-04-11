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

enum Game {
    PONG,
    FLAPPY_BIRD,
    COLORING_BOOK
};

void initWheel();
void initColorBox();
void initBars();
void initPlayer();

void init();

void initGL();

void spinWheel(int val);

void display();

void kbd(unsigned char key, int x, int y);

void kbdS(int key, int x, int y);

void mouse(int button, int state, int x, int y);





#endif //M1OEP_HGSHERID_GRAPHICS_H
