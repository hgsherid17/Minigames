//
// Created by Hannah Sheridan on 4/12/23.
//

#ifndef M1OEP_HGSHERID_OVAL_H
#define M1OEP_HGSHERID_OVAL_H
#include "shape.h"
#include "graphics.h"

class Oval : public Shape {
private:
    double radiusX, radiusY;
public:
    Oval();
    Oval(double radiusX, double radiusY);
    Oval(point center);
    Oval(point center, double radiusX, double radiusY);
    Oval(color fill);
    Oval(color fill, color border);
    Oval(color fill, color border, point center);
    Oval(color fill, color border, point center, double radiusX, double radiusY);
    Oval(color fill, double x, double y);
    Oval(color fill, double x, double y, double radiusX, double radiusY);
    Oval(color fill, color border, double x, double y);
    Oval(color fill, color border, double x, double y, double radiusX, double radiusY);

    /* Getters */
    double getRadiusX();
    double getRadiusY();
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setters */
    void setRadiusX(double x);
    void setRadiusY(double y);

    void draw() const override;

};

#endif //M1OEP_HGSHERID_OVAL_H
