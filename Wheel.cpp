//p
// Created by Hannah Sheridan on 2/24/23.
//
#include "Wheel.h"
#include <vector>

using namespace std;
Wheel::Wheel() {
    fillWheel();
    wedge = 200;
    srand(time(nullptr));
}
Wheel::Wheel(vector<int> wheel) {
    this->wheel = wheel;
    size = wheel.size();
    wedge = wheel[0];
    srand(time(nullptr));
}

vector<int> Wheel::getWheel() {
    return this->wheel;
}
int Wheel::getCurrentWedge() {
    return this->wedge;
}

int Wheel::getSize() {
    return this->size;
}

void Wheel::addWedge(int wedge) {
    wheel.push_back(wedge);
    this->wedge = wedge;
    ++size;
}

bool Wheel::removeWedge(int wedge) {
    if (find(wheel.begin(), wheel.end(), wedge) != wheel.end()) {
        for (int i = 0; i < wheel.size(); ++i) {
            if (wheel[i] == wedge) {
                wheel.erase(wheel.begin() + i);
                --size;
            }
        }
        return true;
    }
    else {
        // Wedge is not in wheel and cannot be removed
        return false;
    }
}
void Wheel::fillWheel() {
    wheel.clear();
    size = 0;
    for (int i = 200; i <= 700; i += 50) {
        wheel.push_back(i);
        wheel.push_back(i);
        size += 2;
    }

    // Highest value prize, lose a turn, and bankrupt are less probable
    wheel.push_back(1000);
    wheel.push_back(2500);
    wheel.push_back(0); // Bankrupt
    wheel.push_back(-1); // Lose a turn
    size += 4;

    wedge = wheel[0];
}
int Wheel::spin() {
    int randIndex = rand() % wheel.size();

    wedge = wheel[randIndex];

    return wedge;

}

ostream& operator << (ostream& outs, Wheel& rhs) {
    int lastWedge;
    for (int i = 0; i < rhs.getSize(); ++i) {
        if (rhs.getWheel()[i] == lastWedge) {
            outs << "";
        }
        else if (rhs.getWheel()[i] == 0) {
            outs << "Bankrupt   ";
        }
        else if (rhs.getWheel()[i] == -1) {
            outs << "Lose a Turn   ";
        }
        else {
            outs << rhs.getWheel()[i] << "   ";
        }

        lastWedge = rhs.getWheel()[i];
    }
    outs << endl;

    return outs;
}