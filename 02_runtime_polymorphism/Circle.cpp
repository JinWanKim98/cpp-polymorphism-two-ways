/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Circle.cpp
 * 
 * Description  : Implementation of Circle class
 */

#include "Circle.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Constructor: Initialize circle with center and radius
Circle::Circle(string name, bool containsWarpSpace, int centerX, int centerY, int radius)
    : ShapeTwoD(name, containsWarpSpace) {
    this->centerX = centerX;
    this->centerY = centerY;
    this->radius = radius;
}

// Compute area of circle using formula: PI * r^2
double Circle::computeArea() const {
    const double PI = 3.14159265359;
    return PI * radius * radius;
}

// Check if point is strictly inside the circle (not on perimeter)
// Using squared distance to avoid floating point errors
bool Circle::isPointInShape(int x, int y) const {
    int dx = x - centerX;
    int dy = y - centerY;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSquared = radius * radius;
    
    // Point is inside if distance^2 < radius^2 (strictly less than)
    return distanceSquared < radiusSquared;
}

// Check if point is exactly on the perimeter
// Using squared distance for exact integer comparison
bool Circle::isPointOnShape(int x, int y) const {
    int dx = x - centerX;
    int dy = y - centerY;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSquared = radius * radius;
    
    // Point is on perimeter if distance^2 == radius^2 (exactly)
    return distanceSquared == radiusSquared;
}

// Generate string representation of circle
string Circle::toString() const {
    stringstream ss;
    
    // Basic information
    ss << "Name : " << name << endl;
    ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
    ss << "Area : " << fixed << setprecision(2) << computeArea() << " units square" << endl;
    
    // Vertices: For circle, only output center and radius
    ss << "Vertices :" << endl;
    ss << "Point [0] : (" << centerX << ", " << centerY << ")" << endl;
    ss << "Radius : " << radius << endl;
    
    // Points on perimeter: Only output 4 cardinal points (N, S, E, W)
    ss << endl << "Points on perimeter : ";
    ss << "(" << centerX << ", " << (centerY + radius) << "), ";  // North
    ss << "(" << centerX << ", " << (centerY - radius) << "), ";  // South
    ss << "(" << (centerX + radius) << ", " << centerY << "), ";  // East
    ss << "(" << (centerX - radius) << ", " << centerY << ")";    // West
    ss << endl;
    
    // Points within shape (strictly inside)
    ss << endl << "Points within shape : ";
    
    bool firstPoint = true;
    // Define bounding box for efficient iteration
    int minX = centerX - radius;
    int maxX = centerX + radius;
    int minY = centerY - radius;
    int maxY = centerY + radius;
    
    // Iterate through all points in bounding box
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (isPointInShape(x, y)) {
                if (!firstPoint) ss << ", ";
                ss << "(" << x << ", " << y << ")";
                firstPoint = false;
            }
        }
    }
    
    if (firstPoint) ss << "none!";
    
    return ss.str();
}
