/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Cross.cpp
 * 
 * Description  : Implementation of Cross class (12-sided polygon)
 */

#include "Cross.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

// Constructor: Initialize cross with 12 vertices
Cross::Cross(string name, bool containsWarpSpace, int x[], int y[])
    : ShapeTwoD(name, containsWarpSpace) {
    for (int i = 0; i < 12; i++) {
        x_coords[i] = x[i];
        y_coords[i] = y[i];
    }
}

// Compute area using Shoelace Formula (also known as Surveyor's Formula)
double Cross::computeArea() const {
    double area = 0.0;
    int j = 11;  // Previous vertex (wraps around)
    
    // Apply Shoelace Formula
    for (int i = 0; i < 12; i++) {
        area += (x_coords[j] + x_coords[i]) * (y_coords[j] - y_coords[i]);
        j = i;  // Move to next vertex
    }
    
    return fabs(area / 2.0);
}

// Check if point is strictly inside the cross using Ray Casting Algorithm
bool Cross::isPointInShape(int x, int y) const {
    bool inside = false;
    int j = 11;  // Previous vertex (wraps around)
    
    // Ray Casting: Cast a ray from the point to infinity and count intersections
    for (int i = 0; i < 12; i++) {
        // Check if ray crosses edge from vertex j to vertex i
        if (((y_coords[i] > y) != (y_coords[j] > y)) &&
            (x < (x_coords[j] - x_coords[i]) * (y - y_coords[i]) / 
             (y_coords[j] - y_coords[i]) + x_coords[i])) {
            inside = !inside;  // Toggle inside/outside
        }
        j = i;  // Move to next edge
    }
    
    return inside;
}

// Check if point is on the perimeter (excluding vertices)
bool Cross::isPointOnShape(int x, int y) const {
    // Check if point is on any of the 12 edges
    for (int i = 0; i < 12; i++) {
        int j = (i + 1) % 12;  // Next vertex (wraps around)
        
        int x1 = x_coords[i], y1 = y_coords[i];
        int x2 = x_coords[j], y2 = y_coords[j];
        
        // Skip if point is exactly at a vertex
        if ((x == x1 && y == y1) || (x == x2 && y == y2)) {
            continue;
        }
        
        // Check if point is on vertical edge
        if (x1 == x2) {
            if (x == x1 && y >= min(y1, y2) && y <= max(y1, y2)) {
                return true;
            }
        }
        // Check if point is on horizontal edge
        else if (y1 == y2) {
            if (y == y1 && x >= min(x1, x2) && x <= max(x1, x2)) {
                return true;
            }
        }
    }
    
    return false;
}

// Generate string representation of cross
string Cross::toString() const {
    stringstream ss;
    
    // Basic information
    ss << "Name : " << name << endl;
    ss << "Special Type : " << (containsWarpSpace ? "WS" : "NS") << endl;
    ss << "Area : " << fixed << setprecision(2) << computeArea() << " units square" << endl;
    
    // Vertices: All 12 points
    ss << "Vertices :" << endl;
    for (int i = 0; i < 12; i++) {
        ss << "Point [" << i << "] : (" << x_coords[i] << ", " << y_coords[i] << ")" << endl;
    }
    
    // Find bounding box for efficient iteration
    int minX = x_coords[0], maxX = x_coords[0];
    int minY = y_coords[0], maxY = y_coords[0];
    
    for (int i = 1; i < 12; i++) {
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
