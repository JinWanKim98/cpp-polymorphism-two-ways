// Point3D.h
// Point3D class - Represents a 3D point with x, y, z coordinates
// Inherits from Point2D (as per assignment requirements)
//
// Additional Attributes:
//   - z (int): Z-coordinate (inherited: x, y from Point2D)
//
// Overridden Methods:
//   - setDistFrOrigin(): Calculates 3D distance using √(x² + y² + z²)
//   - operator<<: Outputs point in format [x, y, z], distFrOrigin : value
//

#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

class Point3D : public Point2D {
private:
    int z;

public:
    // Constructors
    Point3D();
    Point3D(int x, int y, int z);
    
    // Getters
    int getZ() const;
    
    // Setters
    void setZ(int z);
    void setDistFrOrigin();
    
    // Friend function for output
    friend ostream& operator<<(ostream& os, const Point3D& p);
};

#endif
