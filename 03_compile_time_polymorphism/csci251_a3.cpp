// csci251_a3.cpp
// CSCI251 Assignment 3 - Advanced Programming
// 
// Program: Data Processing with Templates, Operator Overloading, and STL
// 
// Description:
//   This program reads 'messy' data from a file containing Point2D, Point3D,
//   Line2D, and Line3D records. It performs the following operations:
//   1. Reads and parses data from user-specified input file
//   2. Removes all duplicate records using template equals() function
//   3. Filters data by record type (Point2D/Point3D/Line2D/Line3D)
//   4. Sorts data based on user-specified criteria
//   5. Displays sorted data with proper formatting
//   6. Stores filtered/sorted data to output file
//
// Key Features:
//   - Generic template functions (scalar_difference, equals)
//   - Operator overloading (<<, for insertion to streams)
//   - STL containers (vector) - NO arrays used
//   - STL algorithms (sort with custom comparators)
//   - Custom output manipulators with setw() and precision()
//   - Inheritance (Point3D extends Point2D, Line3D extends Line2D)
//   - Robust parsing (handles data with or without spaces after commas)
//
// Date: February 2026
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>

#include "MyTemplates.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

using namespace std;

// Global data storage using STL containers
vector<Point2D> point2D_data;
vector<Point3D> point3D_data;
vector<Line2D> line2D_data;
vector<Line3D> line3D_data;

// Current filter and sort settings
enum FilterType { FILTER_POINT2D, FILTER_POINT3D, FILTER_LINE2D, FILTER_LINE3D };
enum SortCriteria { SORT_X, SORT_Y, SORT_Z, SORT_DIST, SORT_PT1_XY, SORT_PT2_XY, SORT_LENGTH };
enum SortOrder { SORT_ASC, SORT_DESC };

FilterType currentFilter = FILTER_POINT2D;
SortCriteria currentSortCriteria = SORT_X;
SortOrder currentSortOrder = SORT_ASC;

// Student information
string studentID = "";
string studentName = "Jin Wan Kim";

// Function declarations
void displayMenu();
void readData();
void specifyFilterCriteria();
void specifySortCriteria();
void specifySortOrder();
void viewData();
void storeData();
void parsePoint2D(const string& line);
void parsePoint3D(const string& line);
void parseLine2D(const string& line);
void parseLine3D(const string& line);
void removeDuplicates();

// Comparator functions for sorting
bool comparePoint2D_X(const Point2D& a, const Point2D& b);
bool comparePoint2D_Y(const Point2D& a, const Point2D& b);
bool comparePoint2D_Dist(const Point2D& a, const Point2D& b);
bool comparePoint3D_X(const Point3D& a, const Point3D& b);
bool comparePoint3D_Y(const Point3D& a, const Point3D& b);
bool comparePoint3D_Z(const Point3D& a, const Point3D& b);
bool comparePoint3D_Dist(const Point3D& a, const Point3D& b);
bool compareLine2D_Pt1XY(const Line2D& a, const Line2D& b);
bool compareLine2D_Pt2XY(const Line2D& a, const Line2D& b);
bool compareLine2D_Length(const Line2D& a, const Line2D& b);
bool compareLine3D_Pt1XY(const Line3D& a, const Line3D& b);
bool compareLine3D_Pt2XY(const Line3D& a, const Line3D& b);
bool compareLine3D_Length(const Line3D& a, const Line3D& b);

int main() {
    int choice;
    
    while (true) {
        displayMenu();
        cout << "\nPlease enter your choice : ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                readData();
                break;
            case 2:
                specifyFilterCriteria();
                break;
            case 3:
                specifySortCriteria();
                break;
            case 4:
                specifySortOrder();
                break;
            case 5:
                viewData();
                break;
            case 6:
                storeData();
                break;
            case 0:
                cout << "\nExiting program. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
    
    return 0;
}

void displayMenu() {
    cout << "\nStudent ID   : " << studentID << endl;
    cout << "Student Name : " << studentName << endl;
    cout << "----------------------------------------------" << endl;
    cout << "\nWelcome to Assn3 program!\n" << endl;
    
    cout << "1)\tRead in data" << endl;
    cout << "2)\tSpecify filtering criteria (current : ";
    
    switch (currentFilter) {
        case FILTER_POINT2D: cout << "Point2D"; break;
        case FILTER_POINT3D: cout << "Point3D"; break;
        case FILTER_LINE2D: cout << "Line2D"; break;
        case FILTER_LINE3D: cout << "Line3D"; break;
    }
    cout << ")" << endl;
    
    cout << "3)\tSpecify sorting criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D:
        case FILTER_POINT3D:
            if (currentSortCriteria == SORT_X) cout << "x-ordinate";
            else if (currentSortCriteria == SORT_Y) cout << "y-ordinate";
            else if (currentSortCriteria == SORT_Z) cout << "z-ordinate";
            else cout << "Dist. Fr Origin";
            break;
        case FILTER_LINE2D:
        case FILTER_LINE3D:
            if (currentSortCriteria == SORT_PT1_XY) cout << "Pt. 1";
            else if (currentSortCriteria == SORT_PT2_XY) cout << "Pt. 2";
            else cout << "Length";
            break;
    }
    cout << ")" << endl;
    
    cout << "4)\tSpecify sorting order (current : ";
    cout << (currentSortOrder == SORT_ASC ? "ASC" : "DSC") << ")" << endl;
    
    cout << "5)\tView data" << endl;
    cout << "6)\tStore data" << endl;
}

void readData() {
    string filename;
    cout << "\nPlease enter filename : ";
    cin >> filename;
    
    ifstream inFile(filename);
    if (!inFile) {
        cout << "\nError opening file!" << endl;
        cout << "\nGoing back to main menu ...\n";
        return;
    }
    
    // Clear existing data
    point2D_data.clear();
    point3D_data.clear();
    line2D_data.clear();
    line3D_data.clear();
    
    string line;
    int recordCount = 0;
    
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        // Parse line based on type
        if (line.find("Point2D") != string::npos) {
            parsePoint2D(line);
            recordCount++;
        }
        else if (line.find("Point3D") != string::npos) {
            parsePoint3D(line);
            recordCount++;
        }
        else if (line.find("Line2D") != string::npos) {
            parseLine2D(line);
            recordCount++;
        }
        else if (line.find("Line3D") != string::npos) {
            parseLine3D(line);
            recordCount++;
        }
    }
    
    inFile.close();
    
    // Remove duplicates
    removeDuplicates();
    
    cout << "\n" << recordCount << " records read in successfully!" << endl;
    cout << "\nGoing back to main menu ...\n";
}

void parsePoint2D(const string& line) {
    // Format: Point2D, [x, y] or Point2D, [x,y] (with or without space)
    size_t pos1 = line.find('[');
    size_t pos2 = line.find(',', pos1);
    size_t pos3 = line.find(']');
    
    if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
        // Extract x value (from [ to ,)
        string x_str = line.substr(pos1 + 1, pos2 - pos1 - 1);
        
        // Extract y value (from , to ])
        // Skip any spaces after comma
        size_t y_start = pos2 + 1;
        while (y_start < pos3 && line[y_start] == ' ') {
            y_start++;
        }
        string y_str = line.substr(y_start, pos3 - y_start);
        
        // Trim any remaining spaces
        // Remove leading/trailing spaces from x_str
        size_t x_first = x_str.find_first_not_of(' ');
        size_t x_last = x_str.find_last_not_of(' ');
        if (x_first != string::npos && x_last != string::npos) {
            x_str = x_str.substr(x_first, x_last - x_first + 1);
        }
        
        // Remove leading/trailing spaces from y_str
        size_t y_first = y_str.find_first_not_of(' ');
        size_t y_last = y_str.find_last_not_of(' ');
        if (y_first != string::npos && y_last != string::npos) {
            y_str = y_str.substr(y_first, y_last - y_first + 1);
        }
        
        int x = stoi(x_str);
        int y = stoi(y_str);
        
        Point2D p(x, y);
        point2D_data.push_back(p);
    }
}

void parsePoint3D(const string& line) {
    // Format: Point3D, [x, y, z] or Point3D, [x,y,z] (with or without spaces)
    size_t pos1 = line.find('[');
    size_t pos2 = line.find(',', pos1);
    size_t pos3 = line.find(',', pos2 + 1);
    size_t pos4 = line.find(']');
    
    if (pos1 != string::npos && pos2 != string::npos && 
        pos3 != string::npos && pos4 != string::npos) {
        
        // Extract x value
        string x_str = line.substr(pos1 + 1, pos2 - pos1 - 1);
        
        // Extract y value
        size_t y_start = pos2 + 1;
        while (y_start < pos3 && line[y_start] == ' ') y_start++;
        string y_str = line.substr(y_start, pos3 - y_start);
        
        // Extract z value
        size_t z_start = pos3 + 1;
        while (z_start < pos4 && line[z_start] == ' ') z_start++;
        string z_str = line.substr(z_start, pos4 - z_start);
        
        // Trim spaces
        auto trim = [](string& s) {
            size_t first = s.find_first_not_of(' ');
            size_t last = s.find_last_not_of(' ');
            if (first != string::npos && last != string::npos) {
                s = s.substr(first, last - first + 1);
            }
        };
        
        trim(x_str);
        trim(y_str);
        trim(z_str);
        
        int x = stoi(x_str);
        int y = stoi(y_str);
        int z = stoi(z_str);
        
        Point3D p(x, y, z);
        point3D_data.push_back(p);
    }
}

void parseLine2D(const string& line) {
    // Format: Line2D, [x1, y1], [x2, y2] or Line2D, [x1,y1], [x2,y2]
    size_t pos1 = line.find('[');
    size_t pos2 = line.find(',', pos1);
    size_t pos3 = line.find(']');
    size_t pos4 = line.find('[', pos3);
    size_t pos5 = line.find(',', pos4);
    size_t pos6 = line.find(']', pos5);
    
    if (pos1 != string::npos && pos2 != string::npos && 
        pos3 != string::npos && pos4 != string::npos &&
        pos5 != string::npos && pos6 != string::npos) {
        
        // Lambda function to trim spaces
        auto trim = [](string& s) {
            size_t first = s.find_first_not_of(' ');
            size_t last = s.find_last_not_of(' ');
            if (first != string::npos && last != string::npos) {
                s = s.substr(first, last - first + 1);
            }
        };
        
        // Extract first point coordinates
        string x1_str = line.substr(pos1 + 1, pos2 - pos1 - 1);
        size_t y1_start = pos2 + 1;
        while (y1_start < pos3 && line[y1_start] == ' ') y1_start++;
        string y1_str = line.substr(y1_start, pos3 - y1_start);
        
        trim(x1_str);
        trim(y1_str);
        
        // Extract second point coordinates
        string x2_str = line.substr(pos4 + 1, pos5 - pos4 - 1);
        size_t y2_start = pos5 + 1;
        while (y2_start < pos6 && line[y2_start] == ' ') y2_start++;
        string y2_str = line.substr(y2_start, pos6 - y2_start);
        
        trim(x2_str);
        trim(y2_str);
        
        int x1 = stoi(x1_str);
        int y1 = stoi(y1_str);
        int x2 = stoi(x2_str);
        int y2 = stoi(y2_str);
        
        Point2D pt1(x1, y1);
        Point2D pt2(x2, y2);
        Line2D l(pt1, pt2);
        line2D_data.push_back(l);
    }
}

void parseLine3D(const string& line) {
    // Format: Line3D, [x1, y1, z1], [x2, y2, z2] or Line3D, [x1,y1,z1], [x2,y2,z2]
    size_t pos1 = line.find('[');
    size_t pos2 = line.find(',', pos1);
    size_t pos3 = line.find(',', pos2 + 1);
    size_t pos4 = line.find(']');
    size_t pos5 = line.find('[', pos4);
    size_t pos6 = line.find(',', pos5);
    size_t pos7 = line.find(',', pos6 + 1);
    size_t pos8 = line.find(']', pos7);
    
    if (pos1 != string::npos && pos2 != string::npos && 
        pos3 != string::npos && pos4 != string::npos &&
        pos5 != string::npos && pos6 != string::npos &&
        pos7 != string::npos && pos8 != string::npos) {
        
        // Lambda function to trim spaces
        auto trim = [](string& s) {
            size_t first = s.find_first_not_of(' ');
            size_t last = s.find_last_not_of(' ');
            if (first != string::npos && last != string::npos) {
                s = s.substr(first, last - first + 1);
            }
        };
        
        // Extract first point coordinates
        string x1_str = line.substr(pos1 + 1, pos2 - pos1 - 1);
        
        size_t y1_start = pos2 + 1;
        while (y1_start < pos3 && line[y1_start] == ' ') y1_start++;
        string y1_str = line.substr(y1_start, pos3 - y1_start);
        
        size_t z1_start = pos3 + 1;
        while (z1_start < pos4 && line[z1_start] == ' ') z1_start++;
        string z1_str = line.substr(z1_start, pos4 - z1_start);
        
        trim(x1_str);
        trim(y1_str);
        trim(z1_str);
        
        // Extract second point coordinates
        string x2_str = line.substr(pos5 + 1, pos6 - pos5 - 1);
        
        size_t y2_start = pos6 + 1;
        while (y2_start < pos7 && line[y2_start] == ' ') y2_start++;
        string y2_str = line.substr(y2_start, pos7 - y2_start);
        
        size_t z2_start = pos7 + 1;
        while (z2_start < pos8 && line[z2_start] == ' ') z2_start++;
        string z2_str = line.substr(z2_start, pos8 - z2_start);
        
        trim(x2_str);
        trim(y2_str);
        trim(z2_str);
        
        int x1 = stoi(x1_str);
        int y1 = stoi(y1_str);
        int z1 = stoi(z1_str);
        int x2 = stoi(x2_str);
        int y2 = stoi(y2_str);
        int z2 = stoi(z2_str);
        
        Point3D pt1(x1, y1, z1);
        Point3D pt2(x2, y2, z2);
        Line3D l(pt1, pt2);
        line3D_data.push_back(l);
    }
}

void removeDuplicates() {
    // Remove duplicates using equals template function
    
    // Point2D duplicates
    for (size_t i = 0; i < point2D_data.size(); i++) {
        for (size_t j = i + 1; j < point2D_data.size(); ) {
            if (equals(point2D_data[i], point2D_data[j])) {
                point2D_data.erase(point2D_data.begin() + j);
            } else {
                j++;
            }
        }
    }
    
    // Point3D duplicates
    for (size_t i = 0; i < point3D_data.size(); i++) {
        for (size_t j = i + 1; j < point3D_data.size(); ) {
            if (equals(point3D_data[i], point3D_data[j])) {
                point3D_data.erase(point3D_data.begin() + j);
            } else {
                j++;
            }
        }
    }
    
    // Line2D duplicates
    for (size_t i = 0; i < line2D_data.size(); i++) {
        for (size_t j = i + 1; j < line2D_data.size(); ) {
            if (equals(line2D_data[i], line2D_data[j])) {
                line2D_data.erase(line2D_data.begin() + j);
            } else {
                j++;
            }
        }
    }
    
    // Line3D duplicates
    for (size_t i = 0; i < line3D_data.size(); i++) {
        for (size_t j = i + 1; j < line3D_data.size(); ) {
            if (equals(line3D_data[i], line3D_data[j])) {
                line3D_data.erase(line3D_data.begin() + j);
            } else {
                j++;
            }
        }
    }
}

void specifyFilterCriteria() {
    cout << "\n[ Specifying filtering criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D: cout << "Point2D"; break;
        case FILTER_POINT3D: cout << "Point3D"; break;
        case FILTER_LINE2D: cout << "Line2D"; break;
        case FILTER_LINE3D: cout << "Line3D"; break;
    }
    cout << ") ]" << endl;
    
    cout << "\na)\tPoint2D records" << endl;
    cout << "b)\tPoint3D records" << endl;
    cout << "c)\tLine2D records" << endl;
    cout << "d)\tLine3D records" << endl;
    
    cout << "\nPlease enter your criteria (a - d) : ";
    char choice;
    cin >> choice;
    
    switch (choice) {
        case 'a': case 'A':
            currentFilter = FILTER_POINT2D;
            currentSortCriteria = SORT_X; // Reset to default
            cout << "Filter criteria successfully set to 'Point2D'!" << endl;
            break;
        case 'b': case 'B':
            currentFilter = FILTER_POINT3D;
            currentSortCriteria = SORT_X; // Reset to default
            cout << "Filter criteria successfully set to 'Point3D'!" << endl;
            break;
        case 'c': case 'C':
            currentFilter = FILTER_LINE2D;
            currentSortCriteria = SORT_PT1_XY; // Reset to default
            cout << "Filter criteria successfully set to 'Line2D'!" << endl;
            break;
        case 'd': case 'D':
            currentFilter = FILTER_LINE3D;
            currentSortCriteria = SORT_PT1_XY; // Reset to default
            cout << "Filter criteria successfully set to 'Line3D'!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    
    cout << "\n...";
    
    // Re-display menu with updated filter
    cout << "\n\n1)\tRead in data" << endl;
    cout << "2)\tSpecify filtering criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D: cout << "Point2D"; break;
        case FILTER_POINT3D: cout << "Point3D"; break;
        case FILTER_LINE2D: cout << "Line2D"; break;
        case FILTER_LINE3D: cout << "Line3D"; break;
    }
    cout << ")" << endl;
    cout << "3)\tSpecify sorting criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D:
        case FILTER_POINT3D:
            if (currentSortCriteria == SORT_X) cout << "x-ordinate";
            else if (currentSortCriteria == SORT_Y) cout << "y-ordinate";
            else if (currentSortCriteria == SORT_Z) cout << "z-ordinate";
            else cout << "Dist. Fr Origin";
            break;
        case FILTER_LINE2D:
        case FILTER_LINE3D:
            if (currentSortCriteria == SORT_PT1_XY) cout << "Pt. 1";
            else if (currentSortCriteria == SORT_PT2_XY) cout << "Pt. 2";
            else cout << "Length";
            break;
    }
    cout << ")" << endl;
    cout << "4)\t..." << endl;
    cout << "5)\t..." << endl;
}

void specifySortCriteria() {
    cout << "\n[ Specifying sorting criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D:
        case FILTER_POINT3D:
            if (currentSortCriteria == SORT_X) cout << "x-ordinate";
            else if (currentSortCriteria == SORT_Y) cout << "y-ordinate";
            else if (currentSortCriteria == SORT_Z) cout << "z-ordinate";
            else cout << "Dist. Fr Origin";
            break;
        case FILTER_LINE2D:
        case FILTER_LINE3D:
            if (currentSortCriteria == SORT_PT1_XY) cout << "Pt. 1";
            else if (currentSortCriteria == SORT_PT2_XY) cout << "Pt. 2";
            else cout << "Length";
            break;
    }
    cout << ") ]" << endl;
    
    if (currentFilter == FILTER_POINT2D) {
        cout << "\na)\tX ordinate value" << endl;
        cout << "b)\tY ordinate value" << endl;
        cout << "c)\tDist. Fr Origin value" << endl;
        
        cout << "\nPlease enter your criteria (a - c) : ";
        char choice;
        cin >> choice;
        
        switch (choice) {
            case 'a': case 'A':
                currentSortCriteria = SORT_X;
                cout << "Sorting criteria successfully set to 'x-ordinate'!" << endl;
                break;
            case 'b': case 'B':
                currentSortCriteria = SORT_Y;
                cout << "Sorting criteria successfully set to 'y-ordinate'!" << endl;
                break;
            case 'c': case 'C':
                currentSortCriteria = SORT_DIST;
                cout << "Sorting criteria successfully set to 'Dist. Fr Origin'!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    else if (currentFilter == FILTER_POINT3D) {
        cout << "\na)\tX ordinate value" << endl;
        cout << "b)\tY ordinate value" << endl;
        cout << "c)\tZ ordinate value" << endl;
        cout << "d)\tDist. Fr Origin value" << endl;
        
        cout << "\nPlease enter your criteria (a - d) : ";
        char choice;
        cin >> choice;
        
        switch (choice) {
            case 'a': case 'A':
                currentSortCriteria = SORT_X;
                cout << "Sorting criteria successfully set to 'x-ordinate'!" << endl;
                break;
            case 'b': case 'B':
                currentSortCriteria = SORT_Y;
                cout << "Sorting criteria successfully set to 'y-ordinate'!" << endl;
                break;
            case 'c': case 'C':
                currentSortCriteria = SORT_Z;
                cout << "Sorting criteria successfully set to 'z-ordinate'!" << endl;
                break;
            case 'd': case 'D':
                currentSortCriteria = SORT_DIST;
                cout << "Sorting criteria successfully set to 'Dist. Fr Origin'!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    else { // Line2D or Line3D
        cout << "\na)\tPt. 1's (x, y) values" << endl;
        cout << "b)\tPt. 2's (x, y) values" << endl;
        cout << "c)\tLength value" << endl;
        
        cout << "\nPlease enter your criteria (a - c) : ";
        char choice;
        cin >> choice;
        
        switch (choice) {
            case 'a': case 'A':
                currentSortCriteria = SORT_PT1_XY;
                cout << "Sorting criteria successfully set to 'Pt. 1'!" << endl;
                break;
            case 'b': case 'B':
                currentSortCriteria = SORT_PT2_XY;
                cout << "Sorting criteria successfully set to 'Pt. 2'!" << endl;
                break;
            case 'c': case 'C':
                currentSortCriteria = SORT_LENGTH;
                cout << "Sorting criteria successfully set to 'Length'!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    cout << "\n...";
    
    // Re-display menu with updated sort criteria
    cout << "\n\n1)\tRead in data" << endl;
    cout << "2)\tSpecify filtering criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D: cout << "Point2D"; break;
        case FILTER_POINT3D: cout << "Point3D"; break;
        case FILTER_LINE2D: cout << "Line2D"; break;
        case FILTER_LINE3D: cout << "Line3D"; break;
    }
    cout << ")" << endl;
    cout << "3)\tSpecify sorting criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D:
        case FILTER_POINT3D:
            if (currentSortCriteria == SORT_X) cout << "x-ordinate";
            else if (currentSortCriteria == SORT_Y) cout << "y-ordinate";
            else if (currentSortCriteria == SORT_Z) cout << "z-ordinate";
            else cout << "Dist. Fr Origin";
            break;
        case FILTER_LINE2D:
        case FILTER_LINE3D:
            if (currentSortCriteria == SORT_PT1_XY) cout << "Pt. 1";
            else if (currentSortCriteria == SORT_PT2_XY) cout << "Pt. 2";
            else cout << "Length";
            break;
    }
    cout << ")" << endl;
    cout << "4)\tSpecify sorting order (current : ";
    cout << (currentSortOrder == SORT_ASC ? "ASC" : "DSC") << ")" << endl;
    cout << "5)\t..." << endl;
}

void specifySortOrder() {
    cout << "\n[ Specifying sorting order (current : ";
    cout << (currentSortOrder == SORT_ASC ? "ASC" : "DSC") << ") ]" << endl;
    
    cout << "\na)\tASC (Ascending order)" << endl;
    cout << "b)\tDSC (Descending order)" << endl;
    
    cout << "\nPlease enter your criteria (a - b) : ";
    char choice;
    cin >> choice;
    
    switch (choice) {
        case 'a': case 'A':
            currentSortOrder = SORT_ASC;
            cout << "Sorting order successfully set to 'ASC'!" << endl;
            break;
        case 'b': case 'B':
            currentSortOrder = SORT_DESC;
            cout << "Sorting order successfully set to 'DSC'!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    
    cout << "\n...";
    
    // Re-display menu with updated sort order
    cout << "\n\n1)\tRead in data" << endl;
    cout << "2)\tSpecify filtering criteria (current : ";
    switch (currentFilter) {
        case FILTER_POINT2D: cout << "Point2D"; break;
        case FILTER_POINT3D: cout << "Point3D"; break;
        case FILTER_LINE2D: cout << "Line2D"; break;
        case FILTER_LINE3D: cout << "Line3D"; break;
    }
    cout << ")" << endl;
    cout << "3)\t..." << endl;
    cout << "4)\tSpecify sorting order (current : ";
    cout << (currentSortOrder == SORT_ASC ? "ASC" : "DSC") << ")" << endl;
    cout << "5)\t..." << endl;
}

void viewData() {
    cout << "\n[ View data ... ]" << endl;
    cout << "filtering criteria : ";
    switch (currentFilter) {
        case FILTER_POINT2D: cout << "Point2D"; break;
        case FILTER_POINT3D: cout << "Point3D"; break;
        case FILTER_LINE2D: cout << "Line2D"; break;
        case FILTER_LINE3D: cout << "Line3D"; break;
    }
    cout << endl;
    
    cout << "sorting criteria : ";
    switch (currentFilter) {
        case FILTER_POINT2D:
        case FILTER_POINT3D:
            if (currentSortCriteria == SORT_X) cout << "x-ordinate";
            else if (currentSortCriteria == SORT_Y) cout << "y-ordinate";
            else if (currentSortCriteria == SORT_Z) cout << "z-ordinate";
            else cout << "Dist. Fr Origin";
            break;
        case FILTER_LINE2D:
        case FILTER_LINE3D:
            if (currentSortCriteria == SORT_PT1_XY) cout << "Pt. 1";
            else if (currentSortCriteria == SORT_PT2_XY) cout << "Pt. 2";
            else cout << "Length";
            break;
    }
    cout << endl;
    
    cout << "sorting order : " << (currentSortOrder == SORT_ASC ? "ASC" : "DSC") << endl;
    cout << endl;
    
    // Display data based on current filter
    if (currentFilter == FILTER_POINT2D) {
        // Sort Point2D data
        vector<Point2D> sortedData = point2D_data;
        
        if (currentSortCriteria == SORT_X) {
            sort(sortedData.begin(), sortedData.end(), comparePoint2D_X);
        } else if (currentSortCriteria == SORT_Y) {
            sort(sortedData.begin(), sortedData.end(), comparePoint2D_Y);
        } else {
            sort(sortedData.begin(), sortedData.end(), comparePoint2D_Dist);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Display header
        cout << setw(6) << right << "X" << setw(6) << right << "Y" << "   " << "Dist. Fr Origin" << endl;
        cout << "- - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.precision(3);
        
        // Display data
        for (const auto& p : sortedData) {
            cout << "[" << setw(4) << p.getX() << "," << setw(4) << p.getY() << "]   ";
            cout << p.getScalarValue() << endl;
        }
    }
    else if (currentFilter == FILTER_POINT3D) {
        // Sort Point3D data
        vector<Point3D> sortedData = point3D_data;
        
        if (currentSortCriteria == SORT_X) {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_X);
        } else if (currentSortCriteria == SORT_Y) {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_Y);
        } else if (currentSortCriteria == SORT_Z) {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_Z);
        } else {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_Dist);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Display header
        cout << setw(6) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z" << "   " << "Dist. Fr Origin" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.precision(3);
        
        // Display data
        for (const auto& p : sortedData) {
            cout << "[" << setw(4) << p.getX() << "," << setw(4) << p.getY() << "," << setw(4) << p.getZ() << "]   ";
            cout << p.getScalarValue() << endl;
        }
    }
    else if (currentFilter == FILTER_LINE2D) {
        // Sort Line2D data
        vector<Line2D> sortedData = line2D_data;
        
        if (currentSortCriteria == SORT_PT1_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine2D_Pt1XY);
        } else if (currentSortCriteria == SORT_PT2_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine2D_Pt2XY);
        } else {
            sort(sortedData.begin(), sortedData.end(), compareLine2D_Length);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Display header
        cout << "P1-X  P1-Y     P2-X  P2-Y     Length" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.precision(3);
        
        // Display data
        for (const auto& l : sortedData) {
            Point2D pt1 = l.getPt1();
            Point2D pt2 = l.getPt2();
            cout << "[" << setw(4) << pt1.getX() << "," << setw(4) << pt1.getY() << "]   ";
            cout << "[" << setw(4) << pt2.getX() << "," << setw(4) << pt2.getY() << "]   ";
            cout << l.getScalarValue() << endl;
        }
    }
    else { // FILTER_LINE3D
        // Sort Line3D data
        vector<Line3D> sortedData = line3D_data;
        
        if (currentSortCriteria == SORT_PT1_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine3D_Pt1XY);
        } else if (currentSortCriteria == SORT_PT2_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine3D_Pt2XY);
        } else {
            sort(sortedData.begin(), sortedData.end(), compareLine3D_Length);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Display header
        cout << "P1-X  P1-Y  P1-Z     P2-X  P2-Y  P2-Z     Length" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout.precision(3);
        
        // Display data
        for (const auto& l : sortedData) {
            Point3D pt1 = l.getPt1();
            Point3D pt2 = l.getPt2();
            cout << "[" << setw(4) << pt1.getX() << "," << setw(4) << pt1.getY() << "," << setw(4) << pt1.getZ() << "]   ";
            cout << "[" << setw(4) << pt2.getX() << "," << setw(4) << pt2.getY() << "," << setw(4) << pt2.getZ() << "]   ";
            cout << l.getScalarValue() << endl;
        }
    }
    
    cout << "\nPress any key to go back to main menu ..." << endl;
    cin.ignore();
    cin.get();
}

void storeData() {
    string filename;
    cout << "\nPlease enter filename : ";
    cin >> filename;
    
    ofstream outFile(filename);
    if (!outFile) {
        cout << "\nError opening file for writing!" << endl;
        cout << "\nGoing back to main menu ...\n";
        return;
    }
    
    int recordCount = 0;
    
    // Store data based on current filter and sorting
    if (currentFilter == FILTER_POINT2D) {
        // Sort Point2D data
        vector<Point2D> sortedData = point2D_data;
        
        if (currentSortCriteria == SORT_X) {
            sort(sortedData.begin(), sortedData.end(), comparePoint2D_X);
        } else if (currentSortCriteria == SORT_Y) {
            sort(sortedData.begin(), sortedData.end(), comparePoint2D_Y);
        } else {
            sort(sortedData.begin(), sortedData.end(), comparePoint2D_Dist);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Write header
        outFile << setw(6) << right << "X" << setw(6) << right << "Y" << "   " << "Dist. Fr Origin" << endl;
        outFile << "- - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        outFile.setf(ios_base::fixed, ios_base::floatfield);
        outFile.precision(3);
        
        // Write data
        for (const auto& p : sortedData) {
            outFile << "[" << setw(4) << p.getX() << "," << setw(4) << p.getY() << "]   ";
            outFile << p.getScalarValue() << endl;
            recordCount++;
        }
    }
    else if (currentFilter == FILTER_POINT3D) {
        // Sort Point3D data
        vector<Point3D> sortedData = point3D_data;
        
        if (currentSortCriteria == SORT_X) {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_X);
        } else if (currentSortCriteria == SORT_Y) {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_Y);
        } else if (currentSortCriteria == SORT_Z) {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_Z);
        } else {
            sort(sortedData.begin(), sortedData.end(), comparePoint3D_Dist);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Write header
        outFile << setw(6) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z" << "   " << "Dist. Fr Origin" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        outFile.setf(ios_base::fixed, ios_base::floatfield);
        outFile.precision(3);
        
        // Write data
        for (const auto& p : sortedData) {
            outFile << "[" << setw(4) << p.getX() << "," << setw(4) << p.getY() << "," << setw(4) << p.getZ() << "]   ";
            outFile << p.getScalarValue() << endl;
            recordCount++;
        }
    }
    else if (currentFilter == FILTER_LINE2D) {
        // Sort Line2D data
        vector<Line2D> sortedData = line2D_data;
        
        if (currentSortCriteria == SORT_PT1_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine2D_Pt1XY);
        } else if (currentSortCriteria == SORT_PT2_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine2D_Pt2XY);
        } else {
            sort(sortedData.begin(), sortedData.end(), compareLine2D_Length);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Write header
        outFile << "P1-X  P1-Y     P2-X  P2-Y     Length" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        outFile.setf(ios_base::fixed, ios_base::floatfield);
        outFile.precision(3);
        
        // Write data
        for (const auto& l : sortedData) {
            Point2D pt1 = l.getPt1();
            Point2D pt2 = l.getPt2();
            outFile << "[" << setw(4) << pt1.getX() << "," << setw(4) << pt1.getY() << "]   ";
            outFile << "[" << setw(4) << pt2.getX() << "," << setw(4) << pt2.getY() << "]   ";
            outFile << l.getScalarValue() << endl;
            recordCount++;
        }
    }
    else { // FILTER_LINE3D
        // Sort Line3D data
        vector<Line3D> sortedData = line3D_data;
        
        if (currentSortCriteria == SORT_PT1_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine3D_Pt1XY);
        } else if (currentSortCriteria == SORT_PT2_XY) {
            sort(sortedData.begin(), sortedData.end(), compareLine3D_Pt2XY);
        } else {
            sort(sortedData.begin(), sortedData.end(), compareLine3D_Length);
        }
        
        if (currentSortOrder == SORT_DESC) {
            reverse(sortedData.begin(), sortedData.end());
        }
        
        // Write header
        outFile << "P1-X  P1-Y  P1-Z     P2-X  P2-Y  P2-Z     Length" << endl;
        outFile << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        
        // Set precision
        outFile.setf(ios_base::fixed, ios_base::floatfield);
        outFile.precision(3);
        
        // Write data
        for (const auto& l : sortedData) {
            Point3D pt1 = l.getPt1();
            Point3D pt2 = l.getPt2();
            outFile << "[" << setw(4) << pt1.getX() << "," << setw(4) << pt1.getY() << "," << setw(4) << pt1.getZ() << "]   ";
            outFile << "[" << setw(4) << pt2.getX() << "," << setw(4) << pt2.getY() << "," << setw(4) << pt2.getZ() << "]   ";
            outFile << l.getScalarValue() << endl;
            recordCount++;
        }
    }
    
    outFile.close();
    
    cout << "\n" << recordCount << " records output successfully!" << endl;
    cout << "\nGoing back to main menu ...\n";
}

// Comparator function implementations

bool comparePoint2D_X(const Point2D& a, const Point2D& b) {
    if (a.getX() != b.getX()) {
        return a.getX() < b.getX();
    }
    return a.getY() < b.getY();
}

bool comparePoint2D_Y(const Point2D& a, const Point2D& b) {
    if (a.getY() != b.getY()) {
        return a.getY() < b.getY();
    }
    return a.getX() < b.getX();
}

bool comparePoint2D_Dist(const Point2D& a, const Point2D& b) {
    return a.getScalarValue() < b.getScalarValue();
}

bool comparePoint3D_X(const Point3D& a, const Point3D& b) {
    if (a.getX() != b.getX()) {
        return a.getX() < b.getX();
    }
    if (a.getY() != b.getY()) {
        return a.getY() < b.getY();
    }
    return a.getZ() < b.getZ();
}

bool comparePoint3D_Y(const Point3D& a, const Point3D& b) {
    if (a.getY() != b.getY()) {
        return a.getY() < b.getY();
    }
    if (a.getX() != b.getX()) {
        return a.getX() < b.getX();
    }
    return a.getZ() < b.getZ();
}

bool comparePoint3D_Z(const Point3D& a, const Point3D& b) {
    if (a.getZ() != b.getZ()) {
        return a.getZ() < b.getZ();
    }
    if (a.getX() != b.getX()) {
        return a.getX() < b.getX();
    }
    return a.getY() < b.getY();
}

bool comparePoint3D_Dist(const Point3D& a, const Point3D& b) {
    return a.getScalarValue() < b.getScalarValue();
}

bool compareLine2D_Pt1XY(const Line2D& a, const Line2D& b) {
    Point2D pt1_a = a.getPt1();
    Point2D pt1_b = b.getPt1();
    
    if (pt1_a.getX() != pt1_b.getX()) {
        return pt1_a.getX() < pt1_b.getX();
    }
    return pt1_a.getY() < pt1_b.getY();
}

bool compareLine2D_Pt2XY(const Line2D& a, const Line2D& b) {
    Point2D pt2_a = a.getPt2();
    Point2D pt2_b = b.getPt2();
    
    if (pt2_a.getX() != pt2_b.getX()) {
        return pt2_a.getX() < pt2_b.getX();
    }
    return pt2_a.getY() < pt2_b.getY();
}

bool compareLine2D_Length(const Line2D& a, const Line2D& b) {
    return a.getScalarValue() < b.getScalarValue();
}

bool compareLine3D_Pt1XY(const Line3D& a, const Line3D& b) {
    Point3D pt1_a = a.getPt1();
    Point3D pt1_b = b.getPt1();
    
    if (pt1_a.getX() != pt1_b.getX()) {
        return pt1_a.getX() < pt1_b.getX();
    }
    return pt1_a.getY() < pt1_b.getY();
}

bool compareLine3D_Pt2XY(const Line3D& a, const Line3D& b) {
    Point3D pt2_a = a.getPt2();
    Point3D pt2_b = b.getPt2();
    
    if (pt2_a.getX() != pt2_b.getX()) {
        return pt2_a.getX() < pt2_b.getX();
    }
    return pt2_a.getY() < pt2_b.getY();
}

bool compareLine3D_Length(const Line3D& a, const Line3D& b) {
    return a.getScalarValue() < b.getScalarValue();
}
