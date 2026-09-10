#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include "GridCell.h"
#include <vector>
#include <string>
using namespace std;

// Declares structures and functions for calculating weather predictions.
struct CityForecast {
    string name;
    int id;
    double avgCloudCover;
    double avgPressure;
    char cloudSymbol;
    char pressureSymbol;
    int rainProbability;
};

// Function prototypes
vector<CityForecast> generateForecasts(GridCell** grid, int rows, int cols);
void displayForecastReport(const vector<CityForecast>& forecasts);
int calculateRainProbability(char cloudSym, char pressureSym);

#endif
