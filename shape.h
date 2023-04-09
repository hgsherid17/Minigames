//
// Created by Hannah Sheridan on 4/9/23.
//

#ifndef M1OEP_HGSHERID_SHAPE_H
#define M1OEP_HGSHERID_SHAPE_H
const double PI = 3.14159265358979323846;

struct color {
    double red;
    double green;
    double blue;
    double alpha;

    color();
    color(double r, double g, double b, double a);
    color(double r, double g, double b);
};
struct point {
    double x;
    double y;

    point();
    point(double x, double y);
};
class Shape {
protected:
    color fill;
    point center;
public:
    Shape();
    Shape(color fill);
    Shape (point center);
    Shape(color fill, point center);
    Shape(double r, double g, double b);
    Shape(double r, double g, double b, double a);
    Shape(double x, double y);
    Shape(double r, double g, double b, double x, double y);
    Shape(double r, double g, double b, double a, double x, double y);
    Shape(double r, double g, double b, point center);
    Shape(double r, double g, double b, double a, point center);
    Shape(color fill, double x, double y);

    virtual ~Shape() = default;

    /* Getters */
    color getColor() const;
    point getPoint() const;
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    double getAlpha() const;
    double getCenterX() const;
    double getCenterY() const;
    virtual double getLeftX() const = 0;
    virtual double getRightX() const = 0;
    virtual double getTopY() const = 0;
    virtual double getBottomY() const = 0;

    /* Setters */
    void setColor(color c);
    void setColor(double r, double g, double b, double a);
    void setRed(double r);
    void setGreen(double g);
    void setBlue(double b);
    void setAlpha(double a);
    void setCenter(point center);
    void setCenter(double x, double y);
    void setCenterX(double x);
    void setCenterY(double y);

    virtual void draw() const = 0;


};
#endif //M1OEP_HGSHERID_SHAPE_H
