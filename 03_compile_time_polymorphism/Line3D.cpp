// Line3D.cpp
#include "Line3D.h"

// Default constructor
// Initializes both parent Line2D and 3D endpoints to origin
Line3D::Line3D() : Line2D(), pt1_3D(), pt2_3D() {
    // Parent Line2D is initialized with default Point2D objects (0,0)
    // Our 3D points are initialized to (0,0,0)
}

// Parameterized constructor
// Creates a Line3D from two Point3D objects
Line3D::Line3D(Point3D pt1, Point3D pt2) 
    : Line2D(Point2D(pt1.getX(), pt1.getY()), Point2D(pt2.getX(), pt2.getY())),
      pt1_3D(pt1), 
      pt2_3D(pt2) {
    // Initialize parent Line2D with 2D projections of the points
    // Store full 3D points in our members for accurate 3D calculations
    setLength();  // Calculate 3D length (overrides parent's 2D length)
}

// Getter for first endpoint
Point3D Line3D::getPt1() const {
    return pt1_3D;
}

// Getter for second endpoint
Point3D Line3D::getPt2() const {
    return pt2_3D;
}

// Setter for first endpoint
void Line3D::setPt1(Point3D pt1) {
    this->pt1_3D = pt1;
    // Also update parent's pt1 with 2D projection
    Line2D::setPt1(Point2D(pt1.getX(), pt1.getY()));
    setLength();  // Recalculate 3D length
}

// Setter for second endpoint
void Line3D::setPt2(Point3D pt2) {
    this->pt2_3D = pt2;
    // Also update parent's pt2 with 2D projection
    Line2D::setPt2(Point2D(pt2.getX(), pt2.getY()));
    setLength();  // Recalculate 3D length
}

// Calculate 3D distance between two endpoints
// Formula: length = √((x1-x2)² + (y1-y2)² + (z1-z2)²)
void Line3D::setLength() {
    int dx = pt1_3D.getX() - pt2_3D.getX();
    int dy = pt1_3D.getY() - pt2_3D.getY();
    int dz = pt1_3D.getZ() - pt2_3D.getZ();
    length = sqrt(dx * dx + dy * dy + dz * dz);
}

// Output operator overload
// Format: ( [x1, y1, z1], distFrOrigin : dist1 to [x2, y2, z2], distFrOrigin : dist2 ), length : len
ostream& operator<<(ostream& os, const Line3D& line) {
    os << "( ";
    
    // Save current format flags
    ios_base::fmtflags oldFlags = os.flags();
    streamsize oldPrecision = os.precision();
    
    // Set fixed precision to 3 decimal places
    os.setf(ios_base::fixed, ios_base::floatfield);
    os.precision(3);
    
    os << line.pt1_3D << " to " << line.pt2_3D << " ), length : " << line.length;
    
    // Restore original format
    os.flags(oldFlags);
    os.precision(oldPrecision);
    
    return os;
}
