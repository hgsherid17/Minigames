//
// Created by Hannah Sheridan on 4/11/23.
//

#ifndef M1OEP_HGSHERID_QUAD_H
#define M1OEP_HGSHERID_QUAD_H

#include "shape.h"
#include "graphics.h"
using namespace std;

class Quad : public Shape {
private:
    unsigned int width;
    unsigned int height;

public:
    Quad();
    Quad(unsigned int width, unsigned int height);
    Quad(color fill);
    Quad(point center);
    Quad(color fill, point center);
    Quad(color fill, double x, double y);
    Quad(color fill, point center, unsigned int width, unsigned int height);
    Quad(double r, double g, double b);
    Quad(double r, double g, double b, double a);
    Quad(double r, double g, double b, point center);
    Quad(double r, double g, double b, double a, point center);
    Quad(double r, double g, double b, point center, unsigned int width, unsigned int height);
    Quad(double r, double g, double b, double a, point center, unsigned int width, unsigned int height);
    Quad(double r, double g, double b, double a, double x, double y, unsigned int width, unsigned int height);

    virtual ~Quad() = default;

    /* Getters */
    unsigned int getWidth();
    unsigned int getHeight();
    double getRightX() const override;
    double getLeftX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setters */
    void setSize(unsigned int w, unsigned int h);
    void setWidth(unsigned int w);
    void setHeight(unsigned int h);

   // bool isOverlapping(const Quad &q) const;
    void draw() const override;


};

#endif //M1OEP_HGSHERID_QUAD_H
