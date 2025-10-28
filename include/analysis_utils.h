#pragma once

#include "TTree.h"
#include <vector>
#include <string>

/**
 * @class TemperatureData
 * @brief Stores temperature measurements and provides basic analysis tools.
 *
 * The class reads (year, month, day, temperature) records from a ROOT TTree
 * and computes the corresponding day-of-year index for each entry.
 */
class TemperatureData {
public:
    // Default constructor (creates an empty dataset).
    TemperatureData();

    // Construct and load data from an existing TTree.
    explicit TemperatureData(TTree* tree);

    // Destructor.
    ~TemperatureData();

    /**
     * @brief Compute mean(yVar) vs xVar using ROOT's TProfile.
     * @param yVar Name of the dependent variable.
     * @param xVar Name of the binning variable.
     * @param nBins Number of histogram bins.
     * @param xMin Lower x-axis bound.
     * @param xMax Upper x-axis bound.
     * @param selection Optional event selection (ROOT cut syntax).
     * @return Pair of vectors: (mean values, uncertainties).
     */
    std::pair<std::vector<double>, std::vector<double>>
    calculateMeanProfile(const std::string& yVar,
                         const std::string& xVar,
                         int nBins,
                         double xMin,
                         double xMax,
                         const std::string& selection = "") const;

    // --- Stored Data ---

    TTree* tree = nullptr;

    std::vector<double> years;
    std::vector<double> months;
    std::vector<double> days;
    std::vector<double> temperatures;
    std::vector<int> dayOfYearVec;

private:
    // No private members needed.
};

/**
 * @brief Return true if the given year is a leap year.
 */
bool isLeapYear(int year);

/**
 * @brief Convert (year, month, day) to the day-of-year index.
 */
int dayOfYear(int year, int month, int day);

/**
 * @brief Open a ROOT file and return the TTree named "tree".
 */
TTree* readTree(const std::string& filename);