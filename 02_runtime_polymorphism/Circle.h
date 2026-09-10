/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Circle.h
 * 
 * Description  : Derived class representing a Circle shape
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "ShapeTwoD.h"

class Circle : public ShapeTwoD {
private:
    int centerX;    // X-coordinate of center
    int centerY;    // Y-coordinate of center
    int radius;     // Radius of circle

public:
    // Constructor: Initialize circle with name, warp space status, center, and radius
    Circle(string name, bool containsWarpSpace, int centerX, int centerY, int radius);
    
    // Override virtual functions from base class
    string toString() const override;
    double computeArea() const override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
};

#endif
