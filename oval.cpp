#include "oval.h"

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

/* Setters */
void Oval::setRadiusX(double x) {
    this->radiusX = x;
}
void Oval::setRadiusY(double y) {
    this->radiusY = y;
}


void Oval::draw() const {



}