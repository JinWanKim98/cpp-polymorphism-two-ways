/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : ShapeTwoD.cpp
 * 
 * Description  : Implementation of ShapeTwoD base class
 */

#include "ShapeTwoD.h"

// Constructor: Initialize shape with name and warp space status
ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace) {
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
}

// Virtual destructor
ShapeTwoD::~ShapeTwoD() {
    // Base class destructor - no dynamic memory to clean up
}

// Return the name of the shape
string ShapeTwoD::getName() const {
    return name;
}

// Return whether shape contains warp space
bool ShapeTwoD::getContainsWarpSpace() const {
    return containsWarpSpace;
}

// Set the name of the shape
void ShapeTwoD::setName(string name) {
    this->name = name;
}

// Set whether shape contains warp space
void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) {
    this->containsWarpSpace = containsWarpSpace;
}
