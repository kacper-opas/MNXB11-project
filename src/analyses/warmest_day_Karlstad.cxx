#include "include/analyses.h"

/**
 * @brief Counts how often each day-of-year is the warmest day in Karlstad.
 *
 * Loops over all years, finds the day with the maximum temperature in each year,
 * and accumulates counts for each day-of-year. Produces a histogram showing which
 * days are most frequently the warmest.
 */
void warmest_day_Karlstad()
{
    // Path to Karlstad preprocessed ROOT tree
    const std::string filename =
        "datasets/root_trees/smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.root";

    // Load TTree and load into TemperatureData class
    TTree* tree = readTree(filename);
    TemperatureData data(tree);

    // Initialize vector to count occurrences for each day-of-year (1–366)
    std::vector<double> dayCounts(366, 0.0);

    // Determine all unique years in the dataset
    std::vector<int> uniqueYears;
    for (double y : data.years)
    {
        int year = static_cast<int>(y);
        if (std::find(uniqueYears.begin(), uniqueYears.end(), year) == uniqueYears.end())
            uniqueYears.push_back(year);
    }

    // Loop over each year to find the warmest day
    for (int year : uniqueYears)
    {
        double maxTemp = -1e6;
        int maxDay = 1;

        // Loop through all entries and check if they belong to the current year
        for (size_t i = 0; i < data.years.size(); ++i)
        {
            if (static_cast<int>(data.years[i]) == year)
            {
                // Update max temperature and corresponding day-of-year
                if (data.temperatures[i] > maxTemp)
                {
                    maxTemp = data.temperatures[i];
                    int month = static_cast<int>(data.months[i]);
                    int day   = static_cast<int>(data.days[i]);
                    maxDay = dayOfYear(year, month, day);
                }
            }
        }

        // Increment count for the corresponding day-of-year
        if (maxDay >= 1 && maxDay <= 366)
            dayCounts[maxDay - 1] += 1.0;
    }

    // Prepare x-axis values (days 1–366)
    std::vector<double> days(366);
    for (int i = 0; i < 366; ++i)
        days[i] = i + 1;

    // Plot histogram of warmest day occurrences
    makeHistogram(
        days,
        dayCounts,
        "Warmest day in Karlstad;Day of the year;Counts",
        "results/warmest_day_Karlstad.png"
    );
}