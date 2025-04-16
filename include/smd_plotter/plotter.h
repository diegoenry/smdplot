#ifndef SMD_PLOTTER_H
#define SMD_PLOTTER_H

#include <vector>
#include <string>
#include <iostream>

/**
 * Extract the 5th and 8th fields from lines starting with "SMD" in a file
 * 
 * @param file_path Path to the text file
 * @param x_values Vector to store the 5th field values (Extension)
 * @param y_values Vector to store the 8th field values (Force)
 */
void extract_smd_fields(const std::string& file_path, std::vector<double>& x_values, std::vector<double>& y_values);

/**
 * Plot data points in the terminal
 * 
 * @param x_values X-coordinate values
 * @param y_values Y-coordinate values
 * @param width Width of the plot (default: 80)
 * @param height Height of the plot (default: 20)
 */
void plot_in_terminal(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                    int width = 80, int height = 20);

#endif // SMD_PLOTTER_H
