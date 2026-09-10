#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include "GridCell.h"
using namespace std;

// Declares functions for reading configuration and data files.
struct ConfigData {
    int gridX_min, gridX_max;
    int gridY_min, gridY_max;
    string cityFile;
    string cloudFile;
    string pressureFile;
};

// Function prototypes
bool readConfigFile(const string& filename, ConfigData& config);
bool readCityFile(const string& filename, GridCell** grid, int rows, int cols);
bool readCloudFile(const string& filename, GridCell** grid, int rows, int cols);
bool readPressureFile(const string& filename, GridCell** grid, int rows, int cols);

#endif
