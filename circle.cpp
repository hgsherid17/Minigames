//
// Created by Hannah Sheridan on 4/9/23.
//
#include "circle.h"
#include <vector>
using namespace std;

Circle::Circle() : Shape(), radius(0) {
}

Circle::Circle(double radius) : Shape() {
    setRadius(radius);
};
Circle::Circle(color fill) : Shape(fill), radius(0) {

}
Circle::Circle(point center) : Shape(center), radius(0) {

}
Circle::Circle(color fill, point center) : Shape(fill, center), radius(0) {

}
Circle::Circle(double r, double g, double b) : Shape(r, g, b), radius(0) {

}
Circle::Circle(double r, double g, double b, double a) : Shape(r, g, b, a), radius(0) {

}
Circle::Circle(double x, double y) : Shape(x, y), radius(0) {

}
Circle::Circle(double r, double g, double b, double x, double y) : Shape(r, g, b, x, y), radius(0) {

}
Circle::Circle(double r, double g, double b, double a, double x, double y) : Shape(r, g, b, a, x, y), radius(0) {

}
Circle::Circle(double r, double g, double b, point center) : Shape(r, g, b, center), radius(0) {

}
Circle::Circle(double r, double g, double b, double a, point center) : Shape (r, g, b, a, center), radius(0) {

}
Circle::Circle(color fill, double x, double y) : Shape(fill, x, y), radius(0) {};

Circle::Circle(color fill, double radius) : Shape(fill) {
    setRadius(radius);
}
Circle::Circle(point center, double radius) : Shape(center) {
    setRadius(radius);
}
Circle::Circle(color fill, point center, double radius) : Shape(fill, center) {
    setRadius(radius);
}
Circle::Circle(double r, double g, double b, double a, double x, double y, double radius) : Shape(r, g, b, a, x, y) {
    setRadius(radius);
}
Circle::Circle(double r, double g, double b, point center, double radius) : Shape(r, g, b, center){
    setRadius(radius);
}
Circle::Circle(double r, double g, double b, double a, point center, double radius) : Shape(r, g, b, a, center) {
    setRadius(radius);
}
Circle::Circle(color fill, double x, double y, double radius) : Shape(fill, x, y) {
    setRadius(radius);
}

double Circle::getRadius() const {
    return radius;
}
double Circle::getLeftX() const {
    return center.x - radius;
}
double Circle::getRightX() const {
    return center.x + radius;
}
double Circle::getTopY() const {
    return center.y - radius;
}
double Circle::getBottomY() const {
    return center.y + radius;
}

void Circle::setRadius(double r) {
    if (r < 0) {
        r = 0;
    }
    this->radius = r;
}

void Circle::draw() const {
    glLineWidth(2.0f);
    glColor3f(fill.red, fill.green, fill.blue);

    /* Outline wheel */
    glBegin(GL_LINE_LOOP);

    glVertex2i(center.x, center.y);

    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2f(center.x + (radius * cos(i)),
                   center.y + (radius * sin(i)));
    }
    glEnd();
}

void Circle::drawWedges(int numWedges, vector<color> wedgeColors) {
    /* Segment wedges */

    int wedgeIndex = 0;
    for (int i = 0; i < numWedges; ++i) {
        float start = i * (2.0 * PI) / numWedges;
        float end = (i + 1) * (2.0 * PI) / numWedges;

        glColor3f(wedgeColors[wedgeIndex].red, wedgeColors[wedgeIndex].green, wedgeColors[wedgeIndex].blue);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(center.x, center.y);
        glVertex2f(center.x + radius * cos(start), center.y + radius * sin(start));
        glVertex2f(center.x + radius * cos(end), center.y + radius * sin(end));
        glEnd();

        if (wedgeIndex == wedgeColors.size() - 1) {
            wedgeIndex = 0;
        }
        else {
            wedgeIndex++;
        }
    }




}