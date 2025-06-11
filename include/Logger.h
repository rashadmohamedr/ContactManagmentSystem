#pragma once
#include "include/ContactManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
using namespace std;
class Logger
{
private:
    ofstream logFile;

public:
    Logger(const string &filename)
    {
        logFile.open(filename, ios::app);
        if (!logFile.is_open())
        {
            cerr << "Error opening log file: " << filename << endl;
        }
    }

    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }
    string current_time_string()
    {
        auto now = std::chrono::system_clock::now();                      // Get current time point
        std::time_t now_time = std::chrono::system_clock::to_time_t(now); // Convert to time_t
        std::tm *local_time = std::localtime(&now_time);                  // Convert to tm struct (local time)

        std::ostringstream oss;
        oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S"); // Format time
        return oss.str();
    }
    void logERROR(const string &message)
    {
        if (logFile.is_open())
        {
            logFile << "ERROR: " << "[" << current_time_string() << "] " << message << endl;
        }
        else
        {
            cerr << "Log file is not open." << endl;
        }
    }
    void logINFO(const string &message)
    {
        if (logFile.is_open())
        {
            logFile << "INFO: " << "[" << current_time_string() << "] " << message << endl;
        }
        else
        {
            cerr << "Log file is not open." << endl;
        }
    }
};