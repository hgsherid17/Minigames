/**
 * Code from Runner GP
 */

#ifndef M1OEP_HGSHERID_CLOUD_H
#define M1OEP_HGSHERID_CLOUD_H

#include "shape.h"
#include "graphics.h"
#include <vector>

using namespace std;

class Cloud {
private:
    vector<unique_ptr<Shape>> shapes;

public:
    // Constructors
    Cloud();
    Cloud(color fill, int x, int y, int width);

    // Move all shapes' x-values by the delta and jump the shapes that are fully negative x-values to be greater than width
    void moveLeftAndJumpX(int deltaX, int width);

    // Returns true if any shape in the cloud overlaps with s; returns false otherwise
    //bool isOverlapping(Rect& r);

    // Draw the cloud
    void draw() const;
};








#endif //M1OEP_HGSHERID_CLOUD_H
