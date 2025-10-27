#include "include/plotting_utils.h"
#include "include/analysis_utils.h"
#include "include/analyses.h"
#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <string>

void mean_temp_January_Lulea()
{
    std::string lulea_tree = "datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";
    TTree *tree = readTree(lulea_tree);

    TemperatureData data(tree);

    int year_min = 1954;
    int year_max = 2024;
    int nbins = year_max - year_min;

    auto [meanJanuaryTemps, _] = data.calculateMeanProfile(
        "temperature",
        "year",
        nbins,
        year_min,
        year_max,
        "month==1");

    std::vector<double> years;
    for (int i = 0; i < nbins; ++i)
    {
        years.push_back(year_min + i);
    }

    makeBarPlot(years, meanJanuaryTemps, "title", "results/mean_temp_January_Lulea.png", 0.0);
}
