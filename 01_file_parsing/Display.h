#ifndef DISPLAY_H
#define DISPLAY_H

#include "GridCell.h"

// Defines functions for printing maps to console.
void displayCityMap(GridCell** grid, int rows, int cols);
void displayCloudIndex(GridCell** grid, int rows, int cols);
void displayCloudSymbols(GridCell** grid, int rows, int cols);
void displayPressureIndex(GridCell** grid, int rows, int cols);
void displayPressureSymbols(GridCell** grid, int rows, int cols);

#endif
