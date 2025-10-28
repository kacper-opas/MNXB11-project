#include "include/analyses.h"
#include "include/analysis_utils.h"
#include "include/plotting_utils.h"

/**
 * @brief Main entry point for temperature analysis.
 *
 * Executes a series of analyses on SMHI temperature datasets:
 * 1. Difference in mean yearly temperature between Luleå and Falsterbo.
 * 2. Mean temperature for each day of the year in Falsterbo.
 * 3. Mean January temperature in Luleå.
 * 4. Most frequent warmest day in Karlstad.
 * 5. Yearly difference between warmest and coldest days in Karlstad.
 */
int main()
{
    // Compare mean temperatures between stations
    diff_in_mean_temp_Lulea_Falsterbo(1950, 2022);

    // Mean daily temperatures for Falsterbo
    mean_temp_each_day_Falsterbo();

    // Mean January temperatures for Luleå
    mean_temp_January_Lulea(1950, 2022);

    // Warmest day analysis for Karlstad
    warmest_day_Karlstad();

    // Warmest vs coldest day differences for Karlstad
    warmest_vs_coldest_Karlstad(1943, 2022);

    return 0;
}
