// Point3D.cpp
#include "Point3D.h"

// Default constructor
Point3D::Point3D() : Point2D(), z(0) {
}

// Parameterized constructor
Point3D::Point3D(int x, int y, int z) : Point2D(x, y), z(z) {
    setDistFrOrigin();
}

// Getter
int Point3D::getZ() const {
    return z;
}

// Setters
void Point3D::setZ(int z) {
    this->z = z;
    setDistFrOrigin();
}

void Point3D::setDistFrOrigin() {
    // distFrOrigin = √(x² + y² + z²)
    distFrOrigin = sqrt(x * x + y * y + z * z);
}

// Output operator overload
ostream& operator<<(ostream& os, const Point3D& p) {
    os << "[" << p.getX() << ", " << p.getY() << ", " << p.z << "], distFrOrigin : ";
    
    // Save current format flags
    ios_base::fmtflags oldFlags = os.flags();
    streamsize oldPrecision = os.precision();
    
    // Set fixed precision to 3 decimal places
    os.setf(ios_base::fixed, ios_base::floatfield);
    os.precision(3);
    
    os << p.getScalarValue();
    
    // Restore original format
    os.flags(oldFlags);
    os.precision(oldPrecision);
    
    return os;
}
