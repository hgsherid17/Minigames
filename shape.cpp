//
// Created by Hannah Sheridan on 4/9/23.
//
#include "shape.h"
using namespace std;

/* Color ConSTRUCtors */
color::color() : red(0.0), green(0.0), blue(0.0), alpha(1.0) {

}
color::color(double r, double g, double b) : red(r), green(g), blue(b), alpha(1.0) {

}
color::color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {

}

/* Point ConSTRUCtors */
point::point() : x(0), y(0) {

}
point::point(double x, double y) : x(x), y(y) {

}

/* Shape Constructors */
Shape::Shape() : fill(0.0, 0.0, 0.0, 1.0), center(0,0), border(0.0, 0.0, 0.0, 1.0){

}
Shape::Shape(color fill) : fill(fill), center(0, 0), border(0.0, 0.0, 0.0, 1.0){

}
Shape::Shape (point center) : fill(0.0, 0.0, 0.0, 1.0), center(center), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(color fill, point center) : fill(fill), center(center), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(color fill, color border, point center) : fill(fill), center(center), border(border) {

}
Shape::Shape(double r, double g, double b) : fill(r, g, b, 1.0), center(0, 0), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(double r, double g, double b, double a) : fill(r, g, b, a), center(0, 0), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(double x, double y) : fill(0.0, 0.0, 0.0, 1.0), center(x, y), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(double r, double g, double b, double x, double y) : fill(r, g, b, 1.0), center(x, y), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(double r, double g, double b, double a, double x, double y) : fill(r, g, b, a), center(x, y), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(double r, double g, double b, point center) : fill(r, g, b, 1.0), center(center), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(double r, double g, double b, double a, point center) : fill(r, g, b, a), center(center), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(color fill, double x, double y) : fill(fill), center(x, y), border(0.0, 0.0, 0.0, 1.0) {

}
Shape::Shape(color fill, color border, double x, double y) : fill(fill), border(border), center(x, y) {

}

color Shape::getColor() const {
    return fill;
}
color Shape::getBorder() const {
    return border;
}
point Shape::getPoint() const {
    return center;
}
double Shape::getXVelocity() const {
    return xVelocity;
}
double Shape::getYVelocity() const {
    return yVelocity;
}
double Shape::getRed() const {
    return fill.red;
}
double Shape::getGreen() const {
    return fill.green;
}
double Shape::getBlue() const {
    return fill.blue;
}
double Shape::getAlpha() const {
    return fill.alpha;
}
double Shape::getCenterX() const {
    return center.x;
}
double Shape::getCenterY() const {
    return center.y;
}

void Shape::setColor(color c) {
    fill = c;
}
void Shape::setColor(double r, double g, double b, double a) {
    fill = {r, g, b, a};
}
void Shape::setVelocity(double x, double y) {
    this->xVelocity = x;
    this->yVelocity = y;
}
void Shape::setXVelocity(double x) {
    this->xVelocity = x;
}
void Shape::setYVelocity(double y) {
    this->yVelocity = y;
}
void Shape::setRed(double r) {
    fill.red = r;
}
void Shape::setGreen(double g) {
    fill.green = g;
}
void Shape::setBlue(double b) {
    fill.blue = b;
}
void Shape::setAlpha(double a) {
    fill.alpha = a;
}
void Shape::setCenter(point center) {
    this->center = center;
}
void Shape::setCenter(double x, double y) {
    center = {x, y};
}
void Shape::setCenterX(double x) {
    center.x = x;
}
void Shape::setCenterY(double y) {
    center.y = y;
}

void Shape::move(double x, double y) {
    center.x += x;
    center.y += y;
}

void Shape::moveX(double x) {
    center.x += x;
}

void Shape::moveY(double y) {
    center.y += y;
}

void Shape::bounceX() {
    xVelocity *= -1;
}
void Shape::bounceY() {
    yVelocity *= -1;
}
bool Shape::isColliding(const Shape &s) {
    if (s.getTopY() < getTopY() && s.getBottomY() > getBottomY()) {
        if (s.getRightX() == getLeftX()) {
            return true;
        }
        if (s.getLeftX() == getRightX()) {
            return true;
        }
    }

    return false;

    /*if (s.getRightX() < getLeftX() || getRightX() < s.getLeftX()) {
        return false;
    }
    // When one is above the other
    if (s.getBottomY() < getTopY() || getBottomY() < s.getTopY()) {
        return false;
    }

    return true;*/

}
bool Shape::isOverlapping(const Shape &s) const {
    // There are only two cases when rectangles are *not* overlapping:
    // When one is to the left of another
    if (s.getRightX() < getLeftX() || getRightX() < s.getLeftX()) {
        return false;
    }
    // When one is above the other
    if (s.getBottomY() < getTopY() || getBottomY() < s.getTopY()) {
        return false;
    }

    return true;
}


