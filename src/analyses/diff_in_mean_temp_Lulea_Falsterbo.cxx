#include <string>
#include <vector>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"
#include "include/analysis_utils.h"
#include "include/plotting_utils.h"
#include "include/analyses.h"

void diff_in_mean_temp_Lulea_Falsterbo()
{
    std::string falsterbo_tree = "datasets/root_trees/smhi-opendata_1_52230_20231007_155448_Falsterbo_preprocessed.root";
    std::string lule_tree = "datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";

    TTree *ftree = readTree(falsterbo_tree);
    TTree *ltree = readTree(lule_tree);

    TemperatureData fdata(ftree);
    TemperatureData ldata(ltree);

    int startyear = 1950;
    int endyear = 2022;
    int yearbins = endyear - startyear;

    auto lavgPair = ldata.calculateMeanProfile("temperature", "year", yearbins, startyear, endyear);
    auto favgPair = fdata.calculateMeanProfile("temperature", "year", yearbins, startyear, endyear);

    auto lavgTemps = lavgPair.first;
    auto favgTemps = favgPair.first;

    std::vector<double> years;
    for (int i = 0; i < yearbins; ++i)
    {
        years.push_back(startyear + i + 0.5);
    }

    std::vector<double> difftemp(lavgTemps.size());
    for (size_t i = 0; i < lavgTemps.size(); ++i)
    {
        difftemp[i] = favgTemps[i] - lavgTemps[i];
    }

    makeBarPlot(years, difftemp, "Difference in mean temperature between Lulea and Falsterbo;Year;Temperature difference [Degrees Celsius]", "results/diff_in_mean_temp_Lulea_Falsterbo.png", 0.0);
}
