#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <limits>
#include <iomanip>

int main() {
    std::string input_file = "smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.csv";
    std::string output_file = "Temp_diff.csv";
    std::ifstream infile(input_file);
    if(!infile.is_open()){
        std::cerr << "Error: Could not open input file.\n";
        return 1;
    }
    std::string line;
    std::map<int, std::pair<double, double>> year_minmax; //year->(min, max)
    bool first_line = true;
    while (std:: getline(infile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string year_str, month_str, day_str, temp_str;
        std::getline(ss, year_str, ',');
        std::getline(ss, month_str, ',');
        std::getline(ss, day_str, ',');
        std::getline(ss, temp_str, ',');
        if(year_str.empty() || temp_str.empty())
            continue;
        //year extraction
        int year = std::stoi(year_str);
        double temp = std::stod(temp_str);
        if(year_minmax.find(year)==year_minmax.end()){
            year_minmax[year] = {temp, temp};
        } else {
            auto &minmax = year_minmax[year];
            if (temp < minmax.first) minmax.first = temp;
            if( temp > minmax.second) minmax.second = temp;
        }
    }
    infile.close();
    std::ofstream outfile(output_file);
    if (!outfile.is_open()) {
        std::cerr << "error: Could not open output file .\n";
        return 1;
    }
    outfile << "Year, Difference\n";
    outfile << std::fixed << std::setprecision(2);
    for (const auto &entry : year_minmax) {
        int year = entry.first;
        double diff = entry.second.second - entry.second.first;
        outfile << year << "," << diff << "\n";
    }
    outfile.close();
    std::cout << "output written to" << output_file << std::endl;
    return 0;
}