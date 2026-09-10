// Line2D.h
// Line2D class - Represents a 2D line segment between two Point2D objects
//
// Attributes:
//   - pt1, pt2 (Point2D): Two endpoints of the line
//   - length (double): Distance between pt1 and pt2
//
// Key Methods:
//   - setLength(): Calculates length using distance formula
//   - getScalarValue(): Returns length (used by template functions)
//   - operator<<: Outputs line in format (pt1 to pt2), length : value
//

#ifndef LINE2D_H
#define LINE2D_H

#include "Point2D.h"

class Line2D {
protected:
    Point2D pt1;
    Point2D pt2;
    double length;

public:
    // Constructors
    Line2D();
    Line2D(Point2D pt1, Point2D pt2);
    
    // Getters
    Point2D getPt1() const;
    Point2D getPt2() const;
    double getScalarValue() const;
    
    // Setters
    void setPt1(Point2D pt1);
    void setPt2(Point2D pt2);
    void setLength();
    
    // Friend function for output
    friend ostream& operator<<(ostream& os, const Line2D& line);
};

#endif
