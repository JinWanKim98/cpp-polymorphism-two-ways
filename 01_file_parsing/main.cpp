#include <iostream>
#include <string>
#include <limits>
#include "GridCell.h"
#include "FileReader.h"
#include "Display.h"
#include "WeatherForecast.h"
using namespace std;

void displayMenu(const string& studentId, const string& studentName);
void waitForEnter();

int main() {
    string studentId, studentName;
    
    cout << "Please enter your Student ID: ";
    getline(cin, studentId);
    
    cout << "Please enter your Student Name: ";
    getline(cin, studentName);
    
    // Pointer for the 2D Grid 
    GridCell** grid = nullptr;
    int rows = 0, cols = 0;
    bool dataLoaded = false; // Flag to check if data is loaded
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu(studentId, studentName);
        cin >> choice;
        cin.ignore(); // Clear buffer
        
        switch (choice) {
            case 1: { // Read Config File
                cout << "[ Read in and process a configuration file ]\n";
                
                // If data already exists, clear memory first to avoid leaks
                if (dataLoaded) {
                    for (int i = 0; i < rows; i++) {
                        delete[] grid[i]; // Delete each row
                    }
                    delete[] grid; // Delete the array of pointers
                    dataLoaded = false;
                }
                
                string configFilename;
                cout << "Please enter config filename : ";
                getline(cin, configFilename);
                
                ConfigData config;
                if (!readConfigFile(configFilename, config)) {
                    cout << "Error reading config!\n";
                    waitForEnter();
                    break;
                }
                
                // Calculate map size
                rows = config.gridY_max - config.gridY_min + 1;
                cols = config.gridX_max - config.gridX_min + 1;
                
                cout << "Reading in GridX_IdxRange ... done!\n";
                cout << "Reading in GridY_IdxRange ... done!\n";
                
                //  MEMORY ALLOCATION Start
                // Allocate memory for rows (array of pointers)
                grid = new GridCell*[rows];
                for (int i = 0; i < rows; i++) {
                    // Allocate memory for columns (actual cells)
                    grid[i] = new GridCell[cols];
                }
                //  MEMORY ALLOCATION End
                
                cout << "\nStoring data from input file :\n";
                // Read data files into the allocated grid
                readCityFile(config.cityFile, grid, rows, cols);
                readCloudFile(config.cloudFile, grid, rows, cols);
                readPressureFile(config.pressureFile, grid, rows, cols);
                
                dataLoaded = true;
                cout << "\nAll records successfully stored.\n";
                waitForEnter();
                break;
            }
            
            case 2: // Display City Map
                if (!dataLoaded) cout << "Error: No data loaded!\n";
                else displayCityMap(grid, rows, cols);
                waitForEnter();
                break;
            
            case 3: // Display Cloud Index
                if (!dataLoaded) cout << "Error: No data loaded!\n";
                else displayCloudIndex(grid, rows, cols);
                waitForEnter();
                break;
            
            case 4: // Display Cloud Symbols
                if (!dataLoaded) cout << "Error: No data loaded!\n";
                else displayCloudSymbols(grid, rows, cols);
                waitForEnter();
                break;
            
            case 5: // Display Pressure Index
                if (!dataLoaded) cout << "Error: No data loaded!\n";
                else displayPressureIndex(grid, rows, cols);
                waitForEnter();
                break;
            
            case 6: // Display Pressure Symbols
                if (!dataLoaded) cout << "Error: No data loaded!\n";
                else displayPressureSymbols(grid, rows, cols);
                waitForEnter();
                break;
            
            case 7: { // Show Forecast Report
                if (!dataLoaded) {
                    cout << "Error: No data loaded!\n";
                } else {
                    cout << "\n";
                    // Call the forecast logic and get results
                    vector<CityForecast> forecasts = generateForecasts(grid, rows, cols);
                    displayForecastReport(forecasts);
                }
                waitForEnter();
                break;
            }
            
            case 8: // Quit
                cout << "Exiting program...\n";
                running = false;
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
                waitForEnter();
        }
    }
    
    //  MEMORY DEALLOCATION
    if (dataLoaded) {
        for (int i = 0; i < rows; i++) {
            delete[] grid[i]; // Free each row first
        }
        delete[] grid; // Free the main pointer array
        cout << "Memory successfully deallocated!\n";
    }
    
    return 0;
}

void displayMenu(const string& studentId, const string& studentName) {
    cout << "\nStudent ID   : " << studentId << "\n";
    cout << "Student Name : " << studentName << "\n";
    cout << "----------------------------------------------\n";
    cout << "Welcome to Weather Information Processing System!\n\n";
    cout << "1) Read in and process a configuration file\n";
    cout << "2) Display city map\n";
    cout << "3) Display cloud coverage map (cloudiness index)\n";
    cout << "4) Display cloud coverage map (LMH symbols)\n";
    cout << "5) Display atmospheric pressure map (pressure index)\n";
    cout << "6) Display atmospheric pressure map (LMH symbols)\n";
    cout << "7) Show weather forecast summary report\n";
    cout << "8) Quit\n\n";
    cout << "Please enter your choice : ";
}

void waitForEnter() {
    cout << "\nPress <enter> to go back to main menu ...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
