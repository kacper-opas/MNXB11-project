#pragma once
#include "TTree.h"

class TemperatureData {
public:
    TemperatureData();
    explicit TemperatureData(TTree* tree);

    ~TemperatureData();

    std::pair<std::vector<double>, std::vector<double>> calculateMeanProfile(const std::string& yVar,
                                             const std::string& xVar,
                                             int nbins,
                                             double xMin,
                                             double xMax,
                                             const std::string& selection = "") const;

    TTree* tree;
    std::vector<double> years;
    std::vector<double> months;
    std::vector<double> days;
    std::vector<double> temperatures;
    std::vector<int> day_of_year;

private:
    
};

bool isLeapYear(int year);
int dayOfYear(int year, int month, int day);

TTree *readTree(const std::string &tree_file);