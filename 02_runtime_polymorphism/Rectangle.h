/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Rectangle.h
 * 
 * Description  : Derived class representing a Rectangle shape
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ShapeTwoD.h"

class Rectangle : public ShapeTwoD {
private:
    int x_coords[4];    // X-coordinates of 4 vertices
    int y_coords[4];    // Y-coordinates of 4 vertices

public:
    // Constructor: Initialize rectangle with name, warp space status, and vertices
    Rectangle(string name, bool containsWarpSpace, int x[], int y[]);
    
    // Override virtual functions from base class
    string toString() const override;
    double computeArea() const override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
};

#endif
