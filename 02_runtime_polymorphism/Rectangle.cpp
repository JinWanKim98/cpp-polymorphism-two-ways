/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Rectangle.cpp
 * 
 * Description  : Implementation of Rectangle class
 */

#include "Rectangle.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Constructor: Initialize rectangle with vertices
Rectangle::Rectangle(string name, bool containsWarpSpace, int x[], int y[])
    : ShapeTwoD(name, containsWarpSpace) {
    for (int i = 0; i < 4; i++) {
        x_coords[i] = x[i];
        y_coords[i] = y[i];
    }
}

// Compute area of rectangle using bounding box
double Rectangle::computeArea() const {
    int minX = x_coords[0], maxX = x_coords[0];
    int minY = y_coords[0], maxY = y_coords[0];
    
    // Find bounding box
    for (int i = 1; i < 4; i++) {
        minX = min(minX, x_coords[i]);
        maxX = max(maxX, x_coords[i]);
        minY = min(minY, y_coords[i]);
        maxY = max(maxY, y_coords[i]);
    }
    
    // Area = width * height
    return (double)(maxX - minX) * (maxY - minY);
}

// Check if point is strictly inside the rectangle (not on perimeter)
bool Rectangle::isPointInShape(int x, int y) const {
    int minX = x_coords[0], maxX = x_coords[0];
    int minY = y_coords[0], maxY = y_coords[0];
    
    // Find bounding box
    for (int i = 1; i < 4; i++) {
        minX = min(minX, x_coords[i]);
        maxX = max(maxX, x_coords[i]);
        minY = min(minY, y_coords[i]);
        maxY = max(maxY, y_coords[i]);
    }
    
    // Point must be strictly inside (not on boundary)
    return (x > minX && x < maxX && y > minY && y < maxY);
}

// Check if point is on the perimeter (excluding vertices)
bool Rectangle::isPointOnShape(int x, int y) const {
    int minX = x_coords[0], maxX = x_coords[0];
    int minY = y_coords[0], maxY = y_coords[0];
    
    // Find bounding box
    for (int i = 1; i < 4; i++) {
        minX = min(minX, x_coords[i]);
        maxX = max(maxX, x_coords[i]);
        minY = min(minY, y_coords[i]);
        maxY = max(maxY, y_coords[i]);
    }
    
    // Check if on vertical edges
    bool onVertical = (x == minX || x == maxX) && (y >= minY && y <= maxY);
    // Check if on horizontal edges
    bool onHorizontal = (y == minY || y == maxY) && (x >= minX && x <= maxX);
    
    // Must be on edge but NOT at vertices
    return (onVertical || onHorizontal) && 
           !(x == minX && y == minY) &&    // Exclude bottom-left vertex
           !(x == minX && y == maxY) &&    // Exclude top-left vertex
           !(x == maxX && y == minY) &&    // Exclude bottom-right vertex
           !(x == maxX && y == maxY);      // Exclude top-right vertex
}

// Generate string representation of rectangle
string Rectangle::toString() const {
    stringstream ss;
    
    // Basic information
    ss << "Name : " << name << endl;
    ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
    ss << "Area : " << fixed << setprecision(0) << computeArea() << " units square" << endl;
    
    // Vertices
    ss << "Vertices :" << endl;
    for (int i = 0; i < 4; i++) {
        ss << "Point [" << i << "] : (" << x_coords[i] << ", " << y_coords[i] << ")" << endl;
    }
    
    // Find bounding box for iteration
    int minX = x_coords[0], maxX = x_coords[0];
    int minY = y_coords[0], maxY = y_coords[0];
    for (int i = 1; i < 4; i++) {
        minX = min(minX, x_coords[i]);
        maxX = max(maxX, x_coords[i]);
        minY = min(minY, y_coords[i]);
        maxY = max(maxY, y_coords[i]);
    }
    
    // Points on perimeter (excluding vertices)
    ss << endl << "Points on perimeter : ";
    bool firstPoint = true;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (isPointOnShape(x, y)) {
                if (!firstPoint) ss << ", ";
                ss << "(" << x << ", " << y << ")";
                firstPoint = false;
            }
        }
    }
    if (firstPoint) ss << "none!";
    ss << endl;
    
    // Points within shape (strictly inside)
    ss << endl << "Points within shape : ";
    firstPoint = true;
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
