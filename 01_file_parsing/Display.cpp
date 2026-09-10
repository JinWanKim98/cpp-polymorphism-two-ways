#include "Display.h"
#include <iostream>
using namespace std;

// Renders the grid maps (City, Cloud, Pressure) to the terminal.
// It iterates from rows-1 down to 0 to match the Y-axis coordinate system.
void displayCityMap(GridCell** grid, int rows, int cols) {
    // Print Top Border
    cout << "#";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n";
    
    // Print Rows (Reverse order: Top to Bottom)
    for (int i = rows - 1; i >= 0; i--) {
        cout << i << " #"; // Y-axis label
        
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].cityId != -1) {
                cout << " " << grid[i][j].cityId;
            } else {
                cout << "  ";
            }
        }
        cout << " #\n";
    }
    
    // Print Bottom Border and X-axis labels
    cout << " ";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n";
    cout << "  ";
    for (int j = 0; j < cols; j++) cout << " " << j;
    cout << "\n";
}

void displayCloudIndex(GridCell** grid, int rows, int cols) {
    cout << "#";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n";
    
    for (int i = rows - 1; i >= 0; i--) {
        cout << i << " #";
        for (int j = 0; j < cols; j++) {
            cout << " " << grid[i][j].cloudIndex;
        }
        cout << " #\n";
    }
    
    cout << " ";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n  ";
    for (int j = 0; j < cols; j++) cout << " " << j;
    cout << "\n";
}

void displayCloudSymbols(GridCell** grid, int rows, int cols) {
    cout << "#";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n";
    
    for (int i = rows - 1; i >= 0; i--) {
        cout << i << " #";
        for (int j = 0; j < cols; j++) {
            cout << " " << grid[i][j].cloudSymbol;
        }
        cout << " #\n";
    }
    
    cout << " ";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n  ";
    for (int j = 0; j < cols; j++) cout << " " << j;
    cout << "\n";
}

void displayPressureIndex(GridCell** grid, int rows, int cols) {
    cout << "#";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n";
    
    for (int i = rows - 1; i >= 0; i--) {
        cout << i << " #";
        for (int j = 0; j < cols; j++) {
            cout << " " << grid[i][j].pressureIndex;
        }
        cout << " #\n";
    }
    
    cout << " ";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n  ";
    for (int j = 0; j < cols; j++) cout << " " << j;
    cout << "\n";
}

void displayPressureSymbols(GridCell** grid, int rows, int cols) {
    cout << "#";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n";
    
    for (int i = rows - 1; i >= 0; i--) {
        cout << i << " #";
        for (int j = 0; j < cols; j++) {
            cout << " " << grid[i][j].pressureSymbol;
        }
        cout << " #\n";
    }
    
    cout << " ";
    for (int j = 0; j < cols; j++) cout << " #";
    cout << " #\n  ";
    for (int j = 0; j < cols; j++) cout << " " << j;
    cout << "\n";
}
