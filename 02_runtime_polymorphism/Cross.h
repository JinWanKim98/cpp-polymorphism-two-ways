/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Cross.h
 * 
 * Description  : Derived class representing a Cross shape (12-sided polygon)
 */

#ifndef CROSS_H
#define CROSS_H

#include "ShapeTwoD.h"

class Cross : public ShapeTwoD {
private:
    int x_coords[12];    // X-coordinates of 12 vertices
    int y_coords[12];    // Y-coordinates of 12 vertices

public:
    // Constructor: Initialize cross with name, warp space status, and vertices
    Cross(string name, bool containsWarpSpace, int x[], int y[]);
    
    // Override virtual functions from base class
    string toString() const override;
    double computeArea() const override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
};

#endif
