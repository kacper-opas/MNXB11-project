#include "include/analyses.h"

/**
 * @brief Compare average yearly temperatures between Luleå and Falsterbo.
 *
 * Computes mean temperature per year for each location, then subtracts
 * Luleå mean temperature from Falsterbo mean temperature to show how
 * coastal vs northern climate differs over time.
 *
 * Produces a bar plot of the temperature difference vs year.
 */
void diff_in_mean_temp_Lulea_Falsterbo(const int yearMin, const int yearMax)
{
    // Paths to the preprocessed ROOT trees for the two stations
    const std::string falsterboTreePath =
        "datasets/root_trees/smhi-opendata_1_52230_20231007_155448_Falsterbo_preprocessed.root";
    const std::string luleaTreePath =
        "datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";

    // Load TTree objects
    TTree* falsterboTree = readTree(falsterboTreePath);
    TTree* luleaTree     = readTree(luleaTreePath);

    // Convert into TemperatureData class objects for analysis
    TemperatureData fData(falsterboTree);
    TemperatureData lData(luleaTree);

    // Define the year range for the comparison
    const int nYearBins = yearMax - yearMin;

    // Compute average yearly temperature profiles
    auto luleaProfile     = lData.calculateMeanProfile("temperature", "year", nYearBins, yearMin, yearMax);
    auto falsterboProfile = fData.calculateMeanProfile("temperature", "year", nYearBins, yearMin, yearMax);

    // Extract mean values
    const std::vector<double>& luleaAvgTemps     = luleaProfile.first;
    const std::vector<double>& falsterboAvgTemps = falsterboProfile.first;

    // Generate x-values (center of each year bin)
    std::vector<double> yearCenters;
    yearCenters.reserve(nYearBins);
    for (int i = 0; i < nYearBins; ++i)
        yearCenters.push_back(yearMin + i + 0.5);

    // Compute temperature difference per year:
    // Falsterbo (coastal south Sweden) minus Luleå (northern inland)
    std::vector<double> tempDifference(luleaAvgTemps.size());
    for (size_t i = 0; i < tempDifference.size(); ++i)
        tempDifference[i] = falsterboAvgTemps[i] - luleaAvgTemps[i];

    // Plot result
    makeBarPlot(
        yearCenters,
        tempDifference,
        "Difference in mean temperature between Lulea and Falsterbo;Year;Temperature difference [°C]",
        "results/diff_in_mean_temp_Lulea_Falsterbo.png",
        /* baseY = */ 0.0
    );
}