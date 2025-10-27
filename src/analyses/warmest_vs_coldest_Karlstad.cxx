#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLine.h"
#include "include/analysis_utils.h"
#include "include/plotting_utils.h"
#include "include/analyses.h"

void warmest_vs_coldest_Karlstad() {
    std::string filename = "datasets/root_trees/smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.root";
    TTree* tree = readTree(filename);

    TemperatureData data(tree);

    double year_min = 1950;
    double year_max = 2024;
    int nbins = year_max - year_min;

    std::vector<double> diffs;
    std::vector<double> years;
    for (int i = 0; i < nbins; ++i) {
        double yr = year_min + i;
        years.push_back(yr + 0.5);
        
        std::vector<double> temps_this_year;
        for (size_t j = 0; j < data.years.size(); ++j) {
            if (static_cast<int>(data.years[j]) == static_cast<int>(yr)) {
                temps_this_year.push_back(data.temperatures[j]);
            }
        }

        if (!temps_this_year.empty()) {
            double minT = *std::min_element(temps_this_year.begin(), temps_this_year.end());
            double maxT = *std::max_element(temps_this_year.begin(), temps_this_year.end());
            diffs.push_back(maxT - minT);
        } else {
            diffs.push_back(0.0);
        }
    }

    makeBarPlot(years, diffs, "Warmest vs. Coldest day in Karlstad;Day of the year;Temperature [Degrees Celsius]", "results/warmest_vs_coldest_Karlstad.png", 40.0);
}
