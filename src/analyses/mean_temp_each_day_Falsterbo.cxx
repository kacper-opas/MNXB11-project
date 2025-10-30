#include "include/analyses.h"

/**
 * @brief Computes the mean daily temperature for Falsterbo over the year.
 *
 * Uses a TProfile to calculate the mean temperature for each day-of-year (1–366),
 * then plots it with error bars representing the standard error.
 */
void mean_temp_each_day_Falsterbo()
{
    // Path to Falsterbo ROOT tree
    const std::string falsterboTreePath =
        "datasets/root_trees/smhi-opendata_1_52230_20231007_155448_Falsterbo_preprocessed.root";

    // Load TTree and load into TemperatureData class
    TTree* tree = readTree(falsterboTreePath);
    TemperatureData data(tree);

    // Define TProfile parameters: one bin per day
    const int nbins = 366;
    const double xMin = 1;
    const double xMax = 367;

    // Fill TProfile with day-of-year vs temperature
    TProfile* prof = new TProfile("prof", "prof", nbins, xMin, xMax);
    for (size_t i = 0; i < data.temperatures.size(); ++i)
        prof->Fill(data.dayOfYearVec[i], data.temperatures[i]);

    // Extract mean and error for each bin
    std::vector<double> means, errors;
    means.reserve(nbins);
    errors.reserve(nbins);

    for (int bin = 1; bin <= prof->GetNbinsX(); ++bin)
    {
        if (prof->GetBinEntries(bin) > 0)
        {
            means.push_back(prof->GetBinContent(bin));
            errors.push_back(prof->GetBinError(bin));
        }
        else
        {
            means.push_back(0.0);
            errors.push_back(0.0);
        }
    }

    delete prof;

    // Prepare x-axis values and x-errors
    std::vector<double> x, ex;
    x.reserve(nbins);
    ex.reserve(nbins);
    for (size_t i = 0; i < means.size(); ++i)
    {
        x.push_back(i + 1);
        ex.push_back(0.0);
    }

    // Draw error graph: mean ± standard error for each day
    makeErrorGraph(
        x, means, ex, errors,
        "Mean temperature on each day of the year in Falsterbo;Day of the year;Mean Temperature [Degrees Celsius]",
        "results/mean_temp_each_day_Falsterbo.png"
    );
}