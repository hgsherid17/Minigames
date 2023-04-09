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
Shape::Shape() : fill(0.0, 0.0, 0.0, 1.0), center(0,0){

}
Shape::Shape(color fill) : fill(fill), center(0, 0){

}
Shape::Shape (point center) : fill(0.0, 0.0, 0.0, 1.0), center(center) {

}
Shape::Shape(color fill, point center) : fill(fill), center(center) {

}
Shape::Shape(double r, double g, double b) : fill(r, g, b, 1.0), center(0, 0) {

}
Shape::Shape(double r, double g, double b, double a) : fill(r, g, b, a), center(0, 0) {

}
Shape::Shape(double x, double y) : fill(0.0, 0.0, 0.0, 1.0), center(x, y) {

}
Shape::Shape(double r, double g, double b, double x, double y) : fill(r, g, b, 1.0), center(x, y) {

}
Shape::Shape(double r, double g, double b, double a, double x, double y) : fill(r, g, b, a), center(x, y) {

}
Shape::Shape(double r, double g, double b, point center) : fill(r, g, b, 1.0), center(center) {

}
Shape::Shape(double r, double g, double b, double a, point center) : fill(r, g, b, a), center(center) {

}
Shape::Shape(color fill, double x, double y) : fill(fill), center(x, y) {

}

color Shape::getColor() const {
    return fill;
}
point Shape::getPoint() const {
    return center;
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
