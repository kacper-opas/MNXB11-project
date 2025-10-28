#include "include/analyses.h"

/**
 * @brief Computes and plots the mean January temperature in Luleå
 *        over a specified range of years.
 *
 * Uses a ROOT TTree to extract data and TemperatureData to calculate
 * mean temperatures for each year, filtered for January (month==1).
 */
void mean_temp_January_Lulea()
{
    // Path to Luleå preprocessed ROOT tree
    const std::string luleaTreePath =
        "datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";

    // Load TTree and load into TemperatureData class
    TTree* tree = readTree(luleaTreePath);
    TemperatureData data(tree);

    // Define the range of years and number of bins
    const int yearMin = 1954;
    const int yearMax = 2024;
    const int nBins = yearMax - yearMin;

    // Compute mean January temperatures per year
    // selection "month==1" ensures only January data is included
    auto [meanJanuaryTemps, _] = data.calculateMeanProfile(
        "temperature",
        "year",
        nBins,
        yearMin,
        yearMax,
        "month==1"
    );

    // Generate x-axis values (years)
    std::vector<double> years;
    years.reserve(nBins);
    for (int i = 0; i < nBins; ++i)
        years.push_back(yearMin + i);

    // Plot mean January temperatures as a bar chart
    makeBarPlot(
        years,
        meanJanuaryTemps,
        "Mean January temperature in Lulea;Year;Mean Temperature [°C]",
        "results/mean_temp_January_Lulea.png",
        /* baseY = */ 0.0
    );
}