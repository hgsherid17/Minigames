#include "quad.h"

Quad::Quad() : Shape(), width(0), height(0) {

}
Quad::Quad(unsigned int width, unsigned int height) : Shape(), width(width), height(height) {

}
Quad::Quad(color fill) : Shape(fill), width(0), height(0) {

}
Quad::Quad(point center) : Shape(center), width(0), height(0) {

}
Quad::Quad(color fill, point center) : Shape(fill, center), width(0), height(0) {

}
Quad::Quad(color fill, double x, double y) : Shape(fill, x, y), width(0), height(0) {

}
Quad::Quad(color fill, point center, unsigned int width, unsigned int height) : Shape(fill, center), width(width), height(height) {

}
Quad::Quad(double r, double g, double b) : Shape(r, g, b), width(0), height(0) {

}
Quad::Quad(double r, double g, double b, double a) : Shape(r, g, b, a), width(0), height(0) {

}
Quad::Quad(double r, double g, double b, point center) : Shape(r, g, b, center), width(0), height(0) {

}
Quad::Quad(double r, double g, double b, double a, point center) : Shape(r, g, b, a, center), width(0), height(0) {

}
Quad::Quad(double r, double g, double b, point center, unsigned int width, unsigned int height) : Shape(r, g, b, center), width(width), height(height) {

}
Quad::Quad(double r, double g, double b, double a, point center, unsigned int width, unsigned int height) : Shape(r, g, b, a, center), width(width), height(height) {

}
Quad::Quad(double r, double g, double b, double a, double x, double y, unsigned int width, unsigned int height) : Shape(r, g, b, a, x, y), width(width), height(height) {

}

/* Getters */
unsigned int Quad::getWidth() {
    return width;
}
unsigned int Quad::getHeight() {
    return height;
}
double Quad::getRightX() const {
    return center.x + (width / 2);
}
double Quad::getLeftX() const {
    return center.x - (width / 2);
}
double Quad::getTopY() const {
    return center.y - (height / 2);
}
double Quad::getBottomY() const {
    return center.y + (height / 2);
}

/* Setters */
void Quad::setSize(unsigned int w, unsigned int h) {
    this->width = w;
    this->height = h;
}
void Quad::setWidth(unsigned int w) {
    this->width = w;
}
void Quad::setHeight(unsigned int h) {
    this->height = h;
}

/*bool Quad::isOverlapping(const Quad &q) const {
    // There are only two cases when rectangles are *not* overlapping:
    // When one is to the left of another
    if (q.getRightX() < getLeftX() || getRightX() < q.getLeftX()) {
        return false;
    }
    // When one is above the other
    if (q.getBottomY() < getTopY() || getBottomY() < q.getTopY()) {
        return false;
    }

    return true;

}*/
void Quad::draw() const{
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_TRIANGLE_STRIP);

    glVertex2f(center.x, center.y);
    glVertex2f(center.x - (width / 2), center.y + (height / 2));
    glVertex2f(center.x + (width / 2), center.y + (height / 2));
    glVertex2f(center.x - (width / 2), center.y - (height / 2));
    glVertex2f(center.x + (width / 2), center.y - (height / 2));
    glEnd();

    glLineWidth(0.5f);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    //glVertex2f(center.x, center.y);

    glVertex2f(center.x - (width / 2), center.y - (height / 2));
    glVertex2f(center.x - (width / 2), center.y + (height / 2));
    glVertex2f(center.x + (width / 2), center.y + (height / 2));
    glVertex2f(center.x + (width / 2), center.y - (height / 2));

    glEnd();
}
