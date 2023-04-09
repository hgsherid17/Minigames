//
// Created by Hannah Sheridan on 4/9/23.
//
#include "circle.h"

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

}