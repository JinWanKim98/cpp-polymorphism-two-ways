// Point2D.cpp
#include "Point2D.h"

// Default constructor
Point2D::Point2D() : x(0), y(0), distFrOrigin(0.0) {
}

// Parameterized constructor
Point2D::Point2D(int x, int y) : x(x), y(y) {
    setDistFrOrigin();
}

// Getters
int Point2D::getX() const {
    return x;
}

int Point2D::getY() const {
    return y;
}

double Point2D::getScalarValue() const {
    return distFrOrigin;
}

// Setters
void Point2D::setX(int x) {
    this->x = x;
    setDistFrOrigin();
}

void Point2D::setY(int y) {
    this->y = y;
    setDistFrOrigin();
}

void Point2D::setDistFrOrigin() {
    // Calculate distance from origin (0,0) using Pythagorean theorem
    // Formula: distFrOrigin = √(x² + y²)
    distFrOrigin = sqrt(x * x + y * y);
}

// Output operator overload
// Format: [x, y], distFrOrigin : value
// Example: [3, 8], distFrOrigin : 8.544
ostream& operator<<(ostream& os, const Point2D& p) {
    os << "[" << p.x << ", " << p.y << "], distFrOrigin : ";
    
    // Save current format flags to restore later
    ios_base::fmtflags oldFlags = os.flags();
    streamsize oldPrecision = os.precision();
    
    // Set fixed precision to 3 decimal places (as per assignment requirements)
    os.setf(ios_base::fixed, ios_base::floatfield);
    os.precision(3);
    
    os << p.distFrOrigin;
    
    // Restore original format to avoid affecting subsequent output
    os.flags(oldFlags);
    os.precision(oldPrecision);
    
    return os;
}
