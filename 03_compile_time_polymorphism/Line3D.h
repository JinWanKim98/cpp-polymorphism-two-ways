// Line3D.h
#ifndef LINE3D_H
#define LINE3D_H

#include "Line2D.h"
#include "Point3D.h"

// Line3D class inherits from Line2D (as per assignment requirements)
// Note: We maintain separate Point3D members (pt1_3D, pt2_3D) because:
//   1. Parent Line2D stores Point2D types, which would lose the z-coordinate
//   2. We need to preserve full 3D information for proper distance calculation
//   3. This is a common pattern when extending 2D geometry to 3D in inheritance hierarchies

class Line3D : public Line2D {
private:
    Point3D pt1_3D;  // 3D version of first endpoint
    Point3D pt2_3D;  // 3D version of second endpoint

public:
    // Constructors
    Line3D();
    Line3D(Point3D pt1, Point3D pt2);
    
    // Getters - return Point3D to preserve z-coordinate
    Point3D getPt1() const;
    Point3D getPt2() const;
    
    // Setters
    void setPt1(Point3D pt1);
    void setPt2(Point3D pt2);
    void setLength();
    
    // Friend function for output
    friend ostream& operator<<(ostream& os, const Line3D& line);
};

#endif
