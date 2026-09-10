// MyTemplates.h
// Generic template functions for scalar_difference and equals
// Used across Point2D, Point3D, Line2D, and Line3D classes

#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

#include <cmath>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

// ============================================================
// Template function: scalar_difference
// Returns the absolute difference in scalar values between two objects
// ============================================================
template <typename T>
double scalar_difference(const T& obj1, const T& obj2) {
    return fabs(obj1.getScalarValue() - obj2.getScalarValue());
}

// ============================================================
// Template function: equals (generic declaration)
// Checks if two objects are equal based on their attributes
// ============================================================
template <typename T>
bool equals(const T& obj1, const T& obj2);

// ============================================================
// Template specialization for Point2D
// Two Point2D objects are equal if x == x AND y == y
// ============================================================
template <>
inline bool equals(const Point2D& obj1, const Point2D& obj2) {
    return (obj1.getX() == obj2.getX()) && (obj1.getY() == obj2.getY());
}

// ============================================================
// Template specialization for Point3D
// Two Point3D objects are equal if x == x AND y == y AND z == z
// ============================================================
template <>
inline bool equals(const Point3D& obj1, const Point3D& obj2) {
    return (obj1.getX() == obj2.getX()) && 
           (obj1.getY() == obj2.getY()) && 
           (obj1.getZ() == obj2.getZ());
}

// ============================================================
// Template specialization for Line2D
// Two Line2D objects are equal if pt1 == pt1 AND pt2 == pt2
// ============================================================
template <>
inline bool equals(const Line2D& obj1, const Line2D& obj2) {
    return equals(obj1.getPt1(), obj2.getPt1()) && 
           equals(obj1.getPt2(), obj2.getPt2());
}

// ============================================================
// Template specialization for Line3D
// Two Line3D objects are equal if pt1 == pt1 AND pt2 == pt2
// ============================================================
template <>
inline bool equals(const Line3D& obj1, const Line3D& obj2) {
    return equals(obj1.getPt1(), obj2.getPt1()) && 
           equals(obj1.getPt2(), obj2.getPt2());
}

// ============================================================
// Template specializations for numeric primitives
// ============================================================
template <>
inline bool equals(const int& obj1, const int& obj2) {
    return obj1 == obj2;
}

template <>
inline bool equals(const double& obj1, const double& obj2) {
    return obj1 == obj2;
}

#endif
