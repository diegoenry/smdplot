#include <iostream>
#include <string>
#include <vector>
#include "smd_plotter/plotter.h"

int main(int argc, char* argv[]) {
    // Check if file path is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }
    
    std::string file_path = argv[1];
    std::vector<double> x_values, y_values;
    
    // Extract data
    extract_smd_fields(file_path, x_values, y_values);
    
    // Check if data was found
    if (x_values.empty() || y_values.empty()) {
        std::cerr << "No valid SMD data found in the file" << std::endl;
        return 1;
    }
    
    // Plot data
    std::cout << "Found " << x_values.size() << " data points. Plotting..." << std::endl;
    plot_in_terminal(x_values, y_values);
    
    return 0;
}
