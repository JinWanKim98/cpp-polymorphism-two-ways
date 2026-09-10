// Line2D.cpp
#include "Line2D.h"

// Default constructor
Line2D::Line2D() : pt1(), pt2(), length(0.0) {
}

// Parameterized constructor
Line2D::Line2D(Point2D pt1, Point2D pt2) : pt1(pt1), pt2(pt2) {
    setLength();
}

// Getters
Point2D Line2D::getPt1() const {
    return pt1;
}

Point2D Line2D::getPt2() const {
    return pt2;
}

double Line2D::getScalarValue() const {
    return length;
}

// Setters
void Line2D::setPt1(Point2D pt1) {
    this->pt1 = pt1;
    setLength();
}

void Line2D::setPt2(Point2D pt2) {
    this->pt2 = pt2;
    setLength();
}

void Line2D::setLength() {
    // length = √((pt1.x - pt2.x)² + (pt1.y - pt2.y)²)
    int dx = pt1.getX() - pt2.getX();
    int dy = pt1.getY() - pt2.getY();
    length = sqrt(dx * dx + dy * dy);
}

// Output operator overload
ostream& operator<<(ostream& os, const Line2D& line) {
    os << "( ";
    
    // Save current format flags
    ios_base::fmtflags oldFlags = os.flags();
    streamsize oldPrecision = os.precision();
    
    // Set fixed precision to 3 decimal places
    os.setf(ios_base::fixed, ios_base::floatfield);
    os.precision(3);
    
    os << line.pt1 << " to " << line.pt2 << " ), length : " << line.length;
    
    // Restore original format
    os.flags(oldFlags);
    os.precision(oldPrecision);
    
    return os;
}
