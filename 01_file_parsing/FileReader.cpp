#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

// Handles all file input operations and parsing.

// Helper function to remove whitespace from strings
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

// Helper to safely convert string to integer
bool safeStoi(const string& str, int& result) {
    try {
        result = stoi(str);
        return true;
    } catch (...) {
        return false;
    }
}

// Helper to keep values within valid range (0-99)
int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Reads the main configuration file
bool readConfigFile(const string& filename, ConfigData& config) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '/') continue; // Skip comments/empty lines
        
        // Parse Grid Ranges
        if (line.find("GridX_IdxRange") != string::npos) {
            size_t pos = line.find('=');
            if (pos == string::npos) continue;
            string range = trim(line.substr(pos + 1));
            size_t dash = range.find('-');
            if (dash != string::npos) {
                safeStoi(trim(range.substr(0, dash)), config.gridX_min);
                safeStoi(trim(range.substr(dash + 1)), config.gridX_max);
            }
        }
        else if (line.find("GridY_IdxRange") != string::npos) {
            size_t pos = line.find('=');
            if (pos == string::npos) continue;
            string range = trim(line.substr(pos + 1));
            size_t dash = range.find('-');
            if (dash != string::npos) {
                safeStoi(trim(range.substr(0, dash)), config.gridY_min);
                safeStoi(trim(range.substr(dash + 1)), config.gridY_max);
            }
        }
        // Identify data filenames based on keywords
        else if (line.find(".txt") != string::npos) {
            if (line.find("city") != string::npos || line.find("location") != string::npos)
                config.cityFile = trim(line);
            else if (line.find("cloud") != string::npos)
                config.cloudFile = trim(line);
            else if (line.find("pressure") != string::npos)
                config.pressureFile = trim(line);
        }
    }
    file.close();
    return true;
}

// Reads city location data
bool readCityFile(const string& filename, GridCell** grid, int rows, int cols) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '/') continue;
        
        // Parse format: [x, y]-id-name
        stringstream ss(line);
        char dummy;
        int x, y, id;
        string name;
        
        ss >> dummy >> x >> dummy >> y >> dummy >> dummy >> id >> dummy;
        getline(ss, name);
        name = trim(name); 
        
        // Boundary Check: Ensure coordinates are valid
        if (y >= 0 && y < rows && x >= 0 && x < cols) {
            grid[y][x].cityId = id;
            grid[y][x].cityName = name;
        }
    }
    file.close();
    return true;
}

// Reads cloud coverage data
bool readCloudFile(const string& filename, GridCell** grid, int rows, int cols) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '/') continue;
        
        stringstream ss(line);
        char dummy;
        int x, y, value;
        ss >> dummy >> x >> dummy >> y >> dummy >> dummy >> value;
        
        // Skip invalid coordinates
        if (y < 0 || y >= rows || x < 0 || x >= cols) continue;
        
        value = clamp(value, 0, 99); // Ensure value is 0-99
        
        grid[y][x].cloudCover = value;
        grid[y][x].cloudIndex = value / 10;
        
        // Assign symbols based on value range
        if (value < 35) grid[y][x].cloudSymbol = 'L';
        else if (value < 65) grid[y][x].cloudSymbol = 'M';
        else grid[y][x].cloudSymbol = 'H';
    }
    file.close();
    return true;
}

// Reads atmospheric pressure data
bool readPressureFile(const string& filename, GridCell** grid, int rows, int cols) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open " << filename << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '/') continue;
        
        stringstream ss(line);
        char dummy;
        int x, y, value;
        ss >> dummy >> x >> dummy >> y >> dummy >> dummy >> value;
        
        if (y < 0 || y >= rows || x < 0 || x >= cols) continue;
        
        value = clamp(value, 0, 99);
        
        grid[y][x].pressure = value;
        grid[y][x].pressureIndex = value / 10;
        
        if (value < 35) grid[y][x].pressureSymbol = 'L';
        else if (value < 65) grid[y][x].pressureSymbol = 'M';
        else grid[y][x].pressureSymbol = 'H';
    }
    file.close();
    return true;
}
