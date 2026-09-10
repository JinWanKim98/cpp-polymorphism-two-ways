/*
 * Student Name : Jin Wan Kim
 * Course Code  : CSCI251
 * Assignment   : 2
 * Filename     : Assn2.cpp
 * 
 * Description  : Main driver program for 2D Shape analysis system
 *                Implements menu-driven interface for managing shape data
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "ShapeTwoD.h"
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Cross.h"

using namespace std;

// Global vector to store all shape objects
vector<ShapeTwoD*> shapeList;

// Helper function: Convert string to lowercase for case-insensitive comparison
string toLowerCase(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Helper function: Capitalize first letter (Square, Rectangle, etc.)
string toProperCase(string str) {
    if (str.empty()) return str;
    str = toLowerCase(str);
    str[0] = toupper(str[0]);
    return str;
}

// Display main menu
void displayMenu() {
    cout << "Student Name : Jin Wan Kim" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Welcome to Assn2 program!" << endl;
    cout << endl;
    cout << "1)\tInput sensor data" << endl;
    cout << "2)\tCompute area (for all records)" << endl;
    cout << "3)\tPrint shapes report" << endl;
    cout << "4)\tSort shape data" << endl;
    cout << endl;
    cout << "Please enter your choice : ";
}

// Menu option 1: Input sensor data for new shapes
void inputSensorData() {
    cout << "[ Input sensor data ]" << endl;
    
    // Get shape name
    string shapeName;
    cout << "Please enter name of shape : ";
    cin >> shapeName;
    
    // Convert to proper case (first letter uppercase, rest lowercase)
    shapeName = toProperCase(shapeName);
    
    // Validate shape name (now case-insensitive)
    if (shapeName != "Square" && shapeName != "Rectangle" && 
        shapeName != "Circle" && shapeName != "Cross") {
        cout << "Invalid shape name! Please enter Square, Rectangle, Circle, or Cross." << endl;
        cout << "Returning to main menu..." << endl;
        cout << endl;
        return;
    }
    
    // Get special type
    string specialType;
    cout << "Please enter special type : ";
    cin >> specialType;
    
    // Convert to uppercase for case-insensitive comparison
    for (size_t i = 0; i < specialType.length(); i++) {
        specialType[i] = toupper(specialType[i]);
    }
    
    // Validate special type (now case-insensitive)
    if (specialType != "WS" && specialType != "NS") {
        cout << "Invalid special type! Please enter WS or NS." << endl;
        cout << "Returning to main menu..." << endl;
        cout << endl;
        return;
    }
    
    bool isWS = (specialType == "WS");
    
    // Input shape-specific data
    if (shapeName == "Square" || shapeName == "Rectangle") {
        // Input 4 vertices for Square/Rectangle
        int x[4], y[4];
        for (int i = 0; i < 4; i++) {
            cout << "Please enter x-ordinate of pt." << (i+1) << " : ";
            cin >> x[i];
            
            // Check if input is valid (not a character)
            if (cin.fail()) {
                cout << "Invalid input! Please enter an integer." << endl;
                cin.clear();  // Clear error state
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Returning to main menu..." << endl;
                cout << endl;
                return;
            }
            
            cout << "Please enter y-ordinate of pt." << (i+1) << " : ";
            cin >> y[i];
            
            // Check if input is valid (not a character)
            if (cin.fail()) {
                cout << "Invalid input! Please enter an integer." << endl;
                cin.clear();  // Clear error state
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Returning to main menu..." << endl;
                cout << endl;
                return;
            }
        }
        
        // Create appropriate shape object
        if (shapeName == "Square") {
            shapeList.push_back(new Square(shapeName, isWS, x, y));
        } else {
            shapeList.push_back(new Rectangle(shapeName, isWS, x, y));
        }
    }
    else if (shapeName == "Circle") {
        // Input center and radius for Circle
        int cx, cy, r;
        
        cout << "Please enter x-ordinate of center : ";
        cin >> cx;
        if (cin.fail()) {
            cout << "Invalid input! Please enter an integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Returning to main menu..." << endl;
            cout << endl;
            return;
        }
        
        cout << "Please enter y-ordinate of center : ";
        cin >> cy;
        if (cin.fail()) {
            cout << "Invalid input! Please enter an integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Returning to main menu..." << endl;
            cout << endl;
            return;
        }
        
        cout << "Please enter radius (units) : ";
        cin >> r;
        if (cin.fail() || r <= 0) {
            cout << "Invalid input! Please enter a positive integer for radius." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Returning to main menu..." << endl;
            cout << endl;
            return;
        }
        
        shapeList.push_back(new Circle(shapeName, isWS, cx, cy, r));
    }
    else if (shapeName == "Cross") {
        // Input 12 vertices for Cross
        int x[12], y[12];
        for (int i = 0; i < 12; i++) {
            cout << "Please enter x-ordinate of pt." << (i+1) << " : ";
            cin >> x[i];
            
            // Check if input is valid (not a character)
            if (cin.fail()) {
                cout << "Invalid input! Please enter an integer." << endl;
                cin.clear();  // Clear error state
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Returning to main menu..." << endl;
                cout << endl;
                return;
            }
            
            cout << "Please enter y-ordinate of pt." << (i+1) << " : ";
            cin >> y[i];
            
            // Check if input is valid (not a character)
            if (cin.fail()) {
                cout << "Invalid input! Please enter an integer." << endl;
                cin.clear();  // Clear error state
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Returning to main menu..." << endl;
                cout << endl;
                return;
            }
        }
        
        shapeList.push_back(new Cross(shapeName, isWS, x, y));
    }
    
    cout << "Record successfully stored. Going back to main menu ..." << endl;
    cout << endl;
}

// Menu option 2: Compute area for all shapes
void computeArea() {
    // Check if there are any shapes
    if (shapeList.empty()) {
        cout << "No records available!" << endl;
        cout << endl;
        return;
    }
    
    // Area is automatically computed when toString() is called
    // This function serves as confirmation that areas are ready
    cout << "Computation completed! ( " << shapeList.size() << " records were updated )" << endl;
    cout << endl;
}

// Menu option 3: Print detailed report of all shapes
void printReport() {
    // Check if there are any shapes
    if (shapeList.empty()) {
        cout << "Total no. of records available = 0" << endl;
        cout << "No records to display!" << endl;
        cout << endl;
        return;
    }
    
    cout << "Total no. of records available = " << shapeList.size() << endl;
    cout << endl;
    
    // Display each shape's details
    for (size_t i = 0; i < shapeList.size(); i++) {
        cout << "Shape [" << i << "]" << endl;
        cout << shapeList[i]->toString() << endl;
        cout << endl;
    }
}

// Menu option 4: Sort shape data
void sortShapeData() {
    // Check if there are any shapes
    if (shapeList.empty()) {
        cout << "No records available to sort!" << endl;
        cout << endl;
        return;
    }
    
    // Display sort options
    cout << "a)\tSort by area (ascending)" << endl;
    cout << "b)\tSort by area (descending)" << endl;
    cout << "c)\tSort by special type and area" << endl;
    cout << endl;
    cout << "Please select sort option ('q' to go main menu) : ";
    
    char option;
    cin >> option;
    
    // Return to main menu if 'q' is pressed
    if (option == 'q' || option == 'Q') {
        cout << endl;
        return;
    }
    
    // Option A: Sort by area (ascending - smallest to largest)
    if (option == 'a') {
        sort(shapeList.begin(), shapeList.end(), 
             [](ShapeTwoD* a, ShapeTwoD* b) {
                 return a->computeArea() < b->computeArea();
             });
        cout << "Sort by area (smallest to largest) ..." << endl;
        cout << endl;
        
        // Display sorted results
        printReport();
    }
    // Option B: Sort by area (descending - largest to smallest)
    else if (option == 'b') {
        sort(shapeList.begin(), shapeList.end(), 
             [](ShapeTwoD* a, ShapeTwoD* b) {
                 return a->computeArea() > b->computeArea();
             });
        cout << "Sort by area (largest to smallest) ..." << endl;
        cout << endl;
        
        // Display sorted results
        printReport();
    }
    // Option C: Sort by special type first (WS before NS), then by area (descending)
    else if (option == 'c') {
        sort(shapeList.begin(), shapeList.end(), 
             [](ShapeTwoD* a, ShapeTwoD* b) {
                 // If different special types, WS comes first
                 if (a->getContainsWarpSpace() != b->getContainsWarpSpace()) {
                     return a->getContainsWarpSpace();  // true (WS) comes before false (NS)
                 }
                 // Within same special type, sort by area (descending)
                 return a->computeArea() > b->computeArea();  // Larger area comes first
             });
        cout << "Sort by special type and area ..." << endl;
        cout << endl;
        
        // Display sorted results
        printReport();
    }
    else {
        cout << "Invalid option! Returning to main menu..." << endl;
        cout << endl;
    }
}

// Main function: Entry point of program
int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;
        
        // Check if input is valid (not a character)
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number (1-4)." << endl;
            cin.clear();  // Clear error state
            cin.ignore(10000, '\n');  // Discard invalid input
            cout << endl;
            continue;  // Go back to menu
        }
        
        cout << endl;
        
        // Process menu choice
        switch (choice) {
            case 1:
                inputSensorData();
                break;
            case 2:
                computeArea();
                break;
            case 3:
                printReport();
                break;
            case 4:
                sortShapeData();
                break;
            default:
                break;
        }
    } while (choice >= 1 && choice <= 4); 
    
    // Cleanup: Free all dynamically allocated memory
    for (auto shape : shapeList) {
        delete shape;
    }
    shapeList.clear();
    
    return 0;
}
