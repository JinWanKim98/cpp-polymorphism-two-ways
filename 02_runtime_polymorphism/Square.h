/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Square.h
 * 
 * Description  : Derived class representing a Square shape
 */

#ifndef SQUARE_H
#define SQUARE_H

#include "ShapeTwoD.h"

class Square : public ShapeTwoD {
private:
    int x_coords[4];    // X-coordinates of 4 vertices
    int y_coords[4];    // Y-coordinates of 4 vertices

public:
    // Constructor: Initialize square with name, warp space status, and vertices
    Square(string name, bool containsWarpSpace, int x[], int y[]);
    
    // Override virtual functions from base class
    string toString() const override;
    double computeArea() const override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
};

#endif
