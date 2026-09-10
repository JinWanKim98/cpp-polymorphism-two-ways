// Point2D.h
// Point2D class - Represents a 2D point with x, y coordinates
// 
// Attributes:
//   - x, y (int): Coordinates of the point
//   - distFrOrigin (double): Distance from origin (0,0)
//
// Key Methods:
//   - setDistFrOrigin(): Calculates distance using formula √(x² + y²)
//   - getScalarValue(): Returns distFrOrigin (used by template functions)
//   - operator<<: Outputs point in format [x, y], distFrOrigin : value
//

#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <cmath>

using namespace std;

class Point2D {
protected:
    int x;
    int y;
    double distFrOrigin;

public:
    // Constructors
    Point2D();
    Point2D(int x, int y);
    
    // Getters
    int getX() const;
    int getY() const;
    double getScalarValue() const;
    
    // Setters
    void setX(int x);
    void setY(int y);
    void setDistFrOrigin();
    
    // Friend function for output
    friend ostream& operator<<(ostream& os, const Point2D& p);
};

#endif
