//
// Created by Hannah Sheridan on 2/24/23.
//

#ifndef M1OEP_HGSHERID_WHEEL_H
#define M1OEP_HGSHERID_WHEEL_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * Wheel class represents a Wheel Of Fortune prize wheel.
 * wedge: the current prize that the wheel has landed on
 * size: the number of wedges on the wheel
 * wheel: a vector holding the wheel's prizes
 */
class Wheel {
private:
    int wedge;
    int size;
    vector<int> wheel;

public:
    // Constructors
    Wheel();
    Wheel(vector<int> wheel);

    // Getters
    int getCurrentWedge();
    int getSize();
    vector<int> getWheel();

    /**
     * addWedge takes in an integer prize value and adds it to the wheel.
     * @param wedge
     */
    void addWedge(int wedge);

    /**
     * removeWedge takes in an integer prize value. If the value is in the wheel, it is removed and the function
     * returns true. Otherwise, it returns false.
     * @param wedge
     * @return true or false
     */
    bool removeWedge(int wedge);

    /**
     * fillWheel fills the wheel with various prize values ranging from 200-2500. It also adds 0
     * to represent the "Bankrupt" wedge, and -1 to represent "Lose a Turn"
     */
    void fillWheel();

    /**
     * spin returns a random value from the wheel
     * @return
     */
    int spin();

    // Overloaded print operator
    friend ostream& operator << (ostream& outs, Wheel& rhs);
};
#endif //M1OEP_HGSHERID_WHEEL_H
