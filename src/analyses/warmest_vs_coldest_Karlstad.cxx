#include "include/analyses.h"

/**
 * @brief Computes and plots the yearly difference between the warmest
 *        and coldest day in Karlstad.
 *
 * For each year in the dataset, finds the maximum and minimum temperature,
 * computes the difference, and plots it as a bar chart over time.
 */
void warmest_vs_coldest_Karlstad()
{
    // Path to Karlstad preprocessed ROOT tree
    const std::string filename =
        "datasets/root_trees/smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.root";

    // Load TTree and load into TemperatureData class
    TTree* tree = readTree(filename);
    TemperatureData data(tree);

    // Define year range and number of bins
    const int yearMin = 1950;
    const int yearMax = 2024;
    const int nBins = yearMax - yearMin;

    // Vectors to store results
    std::vector<double> diffs;
    std::vector<double> years;
    diffs.reserve(nBins);
    years.reserve(nBins);

    // Loop over each year
    for (int i = 0; i < nBins; ++i)
    {
        double year = yearMin + i;
        years.push_back(year + 0.5);

        // Collect all temperatures in this year
        std::vector<double> tempsThisYear;
        for (size_t j = 0; j < data.years.size(); ++j)
        {
            if (static_cast<int>(data.years[j]) == static_cast<int>(year))
                tempsThisYear.push_back(data.temperatures[j]);
        }

        // Compute difference between warmest and coldest day
        if (!tempsThisYear.empty())
        {
            double minT = *std::min_element(tempsThisYear.begin(), tempsThisYear.end());
            double maxT = *std::max_element(tempsThisYear.begin(), tempsThisYear.end());
            diffs.push_back(maxT - minT);
        }
        else
        {
            diffs.push_back(0.0);
        }
    }

    // Plot yearly differences as a bar chart
    makeBarPlot(
        years,
        diffs,
        "Warmest vs. Coldest day in Karlstad;Year;Temperature difference [°C]",
        "results/warmest_vs_coldest_Karlstad.png",
        /* baseY = */ 40.0
    );
}