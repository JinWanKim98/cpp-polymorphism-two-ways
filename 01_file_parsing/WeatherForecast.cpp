#include "WeatherForecast.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Function to determine rain probability based on symbols
int calculateRainProbability(char cloudSym, char pressureSym) {
    if (pressureSym == 'L') {
        if (cloudSym == 'H') return 90; // Low Pressure + High Cloud = 90% Rain
        if (cloudSym == 'M') return 80;
        if (cloudSym == 'L') return 70;
    }
    else if (pressureSym == 'M') {
        if (cloudSym == 'H') return 60;
        if (cloudSym == 'M') return 50;
        if (cloudSym == 'L') return 40;
    }
    else if (pressureSym == 'H') {
        if (cloudSym == 'H') return 30;
        if (cloudSym == 'M') return 20; // High Pressure + Mid Cloud = 20% Rain
        if (cloudSym == 'L') return 10;
    }
    return 0;
}

// Main function to generate weather report
vector<CityForecast> generateForecasts(GridCell** grid, int rows, int cols) {
    vector<CityForecast> forecasts;  // Vector to store results dynamically

    // 1. Loop through all rows
    for (int i = 0; i < rows; i++) {
        // 2. Loop through all columns
        for (int j = 0; j < cols; j++) {

            // Check if this cell is a city. If ID is -1, skip it.
            if (grid[i][j].cityId == -1) continue;

            // Check if city is already in the list (avoid duplicates)
            bool found = false;
            for (const auto& f : forecasts) {
                if (f.id == grid[i][j].cityId) {
                    found = true;
                    break;
                }
            }
            if (found) continue; // If already processed, skip

            // Create a new forecast object
            CityForecast forecast;
            forecast.name = grid[i][j].cityName;
            forecast.id = grid[i][j].cityId;

            double cloudSum = 0;    // To store sum of cloud values
            double pressureSum = 0; // To store sum of pressure values
            int count = 0;          // To count valid neighboring cells

            //  3x3 SCAN ALGORITHM Start
            // Loop from Top(-1) to Bottom(+1)
            for (int di = -1; di <= 1; di++) {
                // Loop from Left(-1) to Right(+1)
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di; // Neighbor Row Index
                    int nj = j + dj; // Neighbor Col Index

                    // Boundary Check
                    // Ensure the neighbor index is INSIDE the map limits
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        cloudSum += grid[ni][nj].cloudCover; // Add cloud value
                        pressureSum += grid[ni][nj].pressure; // Add pressure value
                        count++; // Increment valid cell count
                    }
                }
            }
            //  3x3 SCAN ALGORITHM End

            // Calculate Averages
            forecast.avgCloudCover = cloudSum / count;
            forecast.avgPressure = pressureSum / count;
            
            // Determine Cloud Symbol (L/M/H)
            if (forecast.avgCloudCover < 35) 
                forecast.cloudSymbol = 'L';
            else if (forecast.avgCloudCover < 65) 
                forecast.cloudSymbol = 'M';
            else 
                forecast.cloudSymbol = 'H';

            // Determine Pressure Symbol (L/M/H)
            if (forecast.avgPressure < 35) 
                forecast.pressureSymbol = 'L';
            else if (forecast.avgPressure < 65) 
                forecast.pressureSymbol = 'M';
            else 
                forecast.pressureSymbol = 'H';
            
            // Calculate Rain Probability using the helper function
            forecast.rainProbability = calculateRainProbability(
                forecast.cloudSymbol, forecast.pressureSymbol);
            
            // Add the finished report to the list
            forecasts.push_back(forecast);
        }
    }
    
    return forecasts; // Return the list of forecasts
}

void displayForecastReport(const vector<CityForecast>& forecasts) {
    cout << "Weather Forecast Summary Report\n";
    cout << "--------------------------------\n";
    
    for (const auto& f : forecasts) {
        cout << "City Name : " << f.name << "\n";
        cout << "City ID   : " << f.id << "\n";
        cout << "Ave. Cloud Cover (ACC) : " 
             << fixed << setprecision(2) 
             << f.avgCloudCover << " (" << f.cloudSymbol << ")\n";
        cout << "Ave. Pressure    (AP)  : " 
             << fixed << setprecision(2)
             << f.avgPressure << " (" << f.pressureSymbol << ")\n";
        cout << "Probability of Rain (%) : " 
             << f.rainProbability << ".00\n";
        
        // ASCII Graphics for Rain Probability
        cout << "~~~~\n";
        int bars = f.rainProbability / 10;
        for (int i = 0; i < bars; i++) {
            cout << "~";// Print '~' for probability
        }
        cout << "\n";
        int slashes = (10 - bars) / 2;
        for (int i = 0; i < slashes; i++) {
            cout << "\\"; // Print '\' for remaining space
        }
        cout << "\n";
        cout << "~~~~\n~~~~~\n\\\n\n";
    }
}
