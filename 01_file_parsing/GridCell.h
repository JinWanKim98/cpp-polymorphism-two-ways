#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <string>
using namespace std;

// Defines the basic data structure for a single grid unit.

struct GridCell {
    int cityId;         // Unique ID for the city (-1 if empty)
    string cityName;    // Name of the city
    int cloudCover;     // Cloud coverage value (0-99)
    int pressure;       // Atmospheric pressure value (0-99)
    
    // Processed indices and symbols
    int cloudIndex;     // Single digit index (0-9)
    char cloudSymbol;   // L, M, H symbol
    int pressureIndex;  // Single digit index (0-9)
    char pressureSymbol;// L, M, H symbol
    
    // Constructor to initialize default values
    GridCell() {
        cityId = -1;    // Default: No city here
        cityName = "";
        cloudCover = 0;
        pressure = 0;
        cloudIndex = 0;
        cloudSymbol = ' ';
        pressureIndex = 0;
        pressureSymbol = ' ';
    }
};

#endif
