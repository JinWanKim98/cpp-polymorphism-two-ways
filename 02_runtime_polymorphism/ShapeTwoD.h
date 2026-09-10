/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : ShapeTwoD.h
 * 
 * Description  : Abstract base class for all 2D shapes
 *                Defines interface for shape operations
 */

#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <string>
using namespace std;

class ShapeTwoD {
protected:
    string name;                // Name of the shape (Square, Circle, etc.)
    bool containsWarpSpace;     // Special type: true=WS, false=NS

public:
    // Constructor: Initialize shape with name and warp space status
    ShapeTwoD(string name, bool containsWarpSpace);
    
    // Virtual destructor for proper cleanup of derived classes
    virtual ~ShapeTwoD();
    
    // Getters
    string getName() const;
    bool getContainsWarpSpace() const;
    
    // Setters
    void setName(string name);
    void setContainsWarpSpace(bool containsWarpSpace);
    
    // Pure virtual functions - must be implemented by derived classes
    virtual string toString() const = 0;
    virtual double computeArea() const = 0;
    virtual bool isPointInShape(int x, int y) const = 0;
    virtual bool isPointOnShape(int x, int y) const = 0;
};

#endif
