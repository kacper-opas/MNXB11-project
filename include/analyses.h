#pragma once

// Standard library
#include <vector>
#include <string>
#include <algorithm>

// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TBox.h"
#include "TStyle.h"
#include "TH1F.h"

// Project headers
#include "analysis_utils.h"
#include "plotting_utils.h"

/**
 * @brief Compute and plot the difference in mean yearly temperature
 *        between Luleå and Falsterbo.
 */
void diff_in_mean_temp_Lulea_Falsterbo(const int yearMin, const int yearMax);

/**
 * @brief Compute and plot the mean January temperature in Luleå
 *        for each year in the dataset.
 */
void mean_temp_January_Lulea(const int yearMin, const int yearMax);

/**
 * @brief Compute and plot the difference between the warmest
 *        and coldest day for each year in Karlstad.
 */
void warmest_vs_coldest_Karlstad(const int yearMin, const int yearMax);

/**
 * @brief Count and plot which day-of-year is most often the warmest
 *        in Karlstad across all years.
 */
void warmest_day_Karlstad();

/**
 * @brief Compute and plot the mean temperature for each day of the year
 *        in Falsterbo, with standard error bars.
 */
void mean_temp_each_day_Falsterbo();
