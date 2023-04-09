//
// Created by Hannah Sheridan on 4/9/23.
//

#ifndef M1OEP_HGSHERID_CIRCLE_H
#define M1OEP_HGSHERID_CIRCLE_H
#include "shape.h"

class Circle : public Shape {
private:
    double radius;
public:
    /* Constructors */
    Circle();
    Circle(double radius);
    Circle(color fill);
    Circle(point center);
    Circle(color fill, point center);
    Circle(double r, double g, double b);
    Circle(double r, double g, double b, double a);
    Circle(double x, double y);
    Circle(double r, double g, double b, double x, double y);
    Circle(double r, double g, double b, double a, double x, double y);
    Circle(double r, double g, double b, point center);
    Circle(double r, double g, double b, double a, point center);
    Circle(color fill, double x, double y);
    Circle(color fill, double radius);
    Circle(point center, double radius);
    Circle(color fill, point center, double radius);
    Circle(double r, double g, double b, double a, double x, double y, double radius);
    Circle(double r, double g, double b, point center, double radius);
    Circle(double r, double g, double b, double a, point center, double radius);
    Circle(color fill, double x, double y, double radius);

    virtual ~Circle() = default;

    /* Getters */
    double getRadius() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setters */
    void setRadius(double r);

    void draw() const override;

};

#endif //M1OEP_HGSHERID_CIRCLE_H
