#include "smd_plotter/plotter.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

void extract_smd_fields(const std::string& file_path, std::vector<double>& x_values, std::vector<double>& y_values) {
    std::ifstream file(file_path);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Check if line starts with "SMD"
        if (line.substr(0, 4) == "SMD ") {
            std::istringstream iss(line);
            std::vector<std::string> fields;
            std::string field;
            
            // Split line into fields
            while (iss >> field) {
                fields.push_back(field);
            }
            
            // Check if there are enough fields
            if (fields.size() >= 8) {
                try {
                    // Extract 5th and 8th fields (indices 4 and 7)
                    double x_val = std::stod(fields[4]);
                    double y_val = std::stod(fields[7]);
                    
                    x_values.push_back(x_val);
                    y_values.push_back(y_val);
                }
                catch (const std::invalid_argument& e) {
                    // Skip if fields can't be converted to double
                    continue;
                }
            }
        }
    }
    
    file.close();
}

void plot_in_terminal(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                    int width, int height) {
    if (x_values.empty() || y_values.empty()) return;
   
    // Check if we need to invert (first value higher than last)
    bool invert = x_values[0] > x_values.back();
    
    // Create a copy of x_values with appropriate transformation
    std::vector<double> shifted_x_values;
    double first_x = x_values[0];
    
    if (invert) {
        for (const auto& x : x_values) {
            shifted_x_values.push_back(first_x - x);
        }
       
     } else {
        for (const auto& x : x_values) {
            shifted_x_values.push_back(x - first_x);
         }
    }
    
    // Find min and max values
//    double x_min = *std::min_element(shifted_x_values.begin(), shifted_x_values.end());
    double x_min = 0.0;
    double x_max = *std::max_element(shifted_x_values.begin(), shifted_x_values.end());
    double y_min = *std::min_element(y_values.begin(), y_values.end());
    double y_max = *std::max_element(y_values.begin(), y_values.end());

    // Add some margin
    double x_margin = (x_max - x_min) * 0.1;
    double y_margin = (y_max - y_min) * 0.1;
    x_min -= x_margin;
    x_max += x_margin;
    y_min -= y_margin;
    y_max += y_margin;
    

    // Create chart grid
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));
    
    // Plot points
    for (size_t i = 0; i < shifted_x_values.size(); ++i) {
        int x = static_cast<int>((shifted_x_values[i] - x_min) / (x_max - x_min) * (width - 1));
        int y = static_cast<int>((1.0 - (y_values[i] - y_min) / (y_max - y_min)) * (height - 1));
        
        // Ensure within bounds
        x = std::max(0, std::min(width - 1, x));
        y = std::max(0, std::min(height - 1, y));
        
        grid[y][x] = '*';
    }
    
    // Print title
    std::cout << std::setw(width / 2 + 10) << "SMD Data Analysis" << std::endl << std::endl;
    
    // Print y-axis scale and grid
    for (int y = 0; y < height; ++y) {
        double y_val = y_max - ((double)y / (height - 1)) * (y_max - y_min);
        std::cout << std::setw(8) << std::fixed << std::setprecision(2) << y_val << " |";
        for (int x = 0; x < width; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
    
    // Print x-axis
    std::cout << std::setw(10) << " " << "+";
    for (int x = 0; x < width; ++x) {
        std::cout << "-";
    }
    std::cout << std::endl;
    
    // Print x-axis labels
    /* I tried this spacing bellow to place the numbers at the begining
     * but I'm yet to find the right relation with the x-axis labels
     * se we can actually start the extension from zero.
    std::cout << std::setw(10) << " " << " ";
    */
    for (int i = 0; i < 5; ++i) {
        int pos = i * (width / 4);
        double val = x_min + ((double)pos / (width - 1)) * (x_max - x_min);
        std::cout << std::setw(width / 4) << std::fixed << std::setprecision(2) << val;
    }
    std::cout << std::endl;
    
    // Print x-axis title
    std::cout << std::setw(width / 2 + 10) << "Extension" << std::endl;
}
