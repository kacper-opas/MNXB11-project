#pragma once
#include "TTree.h"

class TemperatureData {
public:
    TemperatureData();
    explicit TemperatureData(TTree* tree);

    ~TemperatureData();

    std::vector<double> calculateMeanProfile(const std::string& yVar,
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

private:
    
};

TTree *readTree(const std::string &tree_file);