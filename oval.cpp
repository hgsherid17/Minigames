#include "oval.h"
using namespace std;

Oval::Oval() : Shape() {

}
Oval::Oval(double radiusX, double radiusY) : radiusX(radiusX), radiusY(radiusY) {

}
Oval::Oval(point center) : Shape(center) {

}
Oval::Oval(point center, double radiusX, double radiusY) : Shape(center), radiusX(radiusX), radiusY(radiusY) {

}
Oval::Oval(color fill) : Shape(fill), radiusX(0), radiusY(0) {

}
Oval::Oval(color fill, color border) : Shape(fill, border), radiusX(0), radiusY(0) {

}
Oval::Oval(color fill, color border, point center) : Shape(fill, border, center), radiusX(0), radiusY(0) {

}
Oval::Oval(color fill, color border, point center, double radiusX, double radiusY) : Shape(fill, border, center), radiusX(radiusX), radiusY(radiusY) {

}
Oval::Oval(color fill, double x, double y) : Shape(fill, x, y), radiusX(0), radiusY(0) {

}
Oval::Oval(color fill, double x, double y, double radiusX, double radiusY) : Shape(fill, x, y), radiusX(radiusX), radiusY(radiusY) {

}
Oval::Oval(color fill, color border, double x, double y) : Shape(fill, border, x, y), radiusX(0), radiusY(0) {

}
Oval::Oval(color fill, color border, double x, double y, double radiusX, double radiusY) : Shape(fill, border, x, y), radiusX(radiusX), radiusY(radiusY) {

}

/* Getters */
double Oval::getRadiusX() {
    return radiusX;
}
double Oval::getRadiusY() {
    return radiusY;
}
double Oval::getLeftX() const {
    return center.x - radiusX;
}
double Oval::getRightX() const {
    return center.x + radiusX;
}
double Oval::getTopY() const  {
    return center.y - radiusY;
}
double Oval::getBottomY() const {
    return center.y + radiusY;
}

/* Setters */
void Oval::setRadiusX(double x) {
    this->radiusX = x;
}
void Oval::setRadiusY(double y) {
    this->radiusY = y;
}


void Oval::draw() const {
    /* Draw Fill */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(fill.red, fill.green, fill.blue);

    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2f(center.x + (radiusX * cos(i)),
                   center.y + (radiusY * sin(i)));
    }

    glEnd();


    /* Draw Outline */
    glBegin(GL_LINE_LOOP);
    glLineWidth(1.0f);
    glColor3f(border.red, border.green, border.blue);

    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2f(center.x + (radiusX * cos(i)),
                   center.y + (radiusY * sin(i)));
    }

    glEnd();


}
void Oval::drawRotated(double angle) const {
    glPushMatrix();
    glTranslatef(center.x, center.y, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-center.x, -center.y, 0.0f);

    /* Draw Fill */
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(fill.red, fill.green, fill.blue);

    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2f(center.x + (radiusX * cos(i)),
                   center.y + (radiusY * sin(i)));
    }

    glEnd();


    /* Draw Outline */
    glBegin(GL_LINE_LOOP);
    glLineWidth(1.0f);
    glColor3f(border.red, border.green, border.blue);

    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2f(center.x + (radiusX * cos(i)),
                   center.y + (radiusY * sin(i)));
    }

    glEnd();

    glPopMatrix();
}