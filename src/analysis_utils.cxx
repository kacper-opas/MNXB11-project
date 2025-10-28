/**
 * @file analysis_utils.cpp
 * @brief Helper functions and TemperatureData implementation.
 */

#include "include/analysis_utils.h"
#include "TFile.h"
#include "TProfile.h"
#include "TDirectory.h"

/**
 * @brief Returns true if the given year is a leap year.
 */
bool isLeapYear(int year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

/**
 * @brief Converts a date to the day-of-year (1–365/366).
 */
int dayOfYear(int year, int month, int day)
{
    static const int daysNormal[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    static const int daysLeap[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

    return (isLeapYear(year) ? daysLeap : daysNormal)[month - 1] + day;
}

/**
 * @brief Opens a ROOT file and returns the TTree named "tree".
 */
TTree *readTree(const std::string &filename)
{
    TFile *file = TFile::Open(filename.c_str(), "READ"); // Load ROOT file from disk
    return dynamic_cast<TTree *>(file->Get("tree"));     // Return pointer to stored TTree
}

/**
 * @brief Default constructor.
 */
TemperatureData::TemperatureData() = default;

/**
 * @brief Default destructor.
 */
TemperatureData::~TemperatureData() = default;

/**
 * @brief Loads temperature data from a TTree with branches: year, month, day, temperature.
 */
TemperatureData::TemperatureData(TTree *inputTree)
{
    tree = inputTree;
    double y = 0, m = 0, d = 0, temp = 0;

    // Link branch names to the temporary variables
    tree->SetBranchAddress("year", &y);
    tree->SetBranchAddress("month", &m);
    tree->SetBranchAddress("day", &d);
    tree->SetBranchAddress("temperature", &temp);

    // Pre-allocate vectors
    const Int_t n = tree->GetEntries();
    years.reserve(n);
    months.reserve(n);
    days.reserve(n);
    temperatures.reserve(n);
    dayOfYearVec.reserve(n);

    // Extract and store all data from the tree
    for (Int_t i = 0; i < n; ++i)
    {
        tree->GetEntry(i); // Load the i-th row into temporary variables

        years.push_back(y);
        months.push_back(m);
        days.push_back(d);
        temperatures.push_back(temp);

        // Convert date to continuous day index and store
        dayOfYearVec.push_back(dayOfYear(static_cast<int>(y),
                                         static_cast<int>(m),
                                         static_cast<int>(d)));
    }
}

/**
 * @brief Computes the mean profile of yVar vs xVar using ROOT's TProfile.
 *
 * @return Pair of (mean values, errors) for each bin.
 */
std::pair<std::vector<double>, std::vector<double>>
TemperatureData::calculateMeanProfile(const std::string &yVar,
                                      const std::string &xVar,
                                      int nBins,
                                      double xMin,
                                      double xMax,
                                      const std::string &selection) const
{
    // Create a new TProfile
    TProfile *prof = new TProfile("prof", "prof", nBins, xMin, xMax);

    // Construct the drawing command for the TTree
    std::string drawCmd = yVar + ":" + xVar + ">>prof";

    // Fill the profile from the tree
    tree->Draw(drawCmd.c_str(), selection.c_str(), "goff"); // "goff" = graphics off

    // Prepare vectors to store mean values and their errors
    std::vector<double> means;
    std::vector<double> errors;
    means.reserve(nBins);
    errors.reserve(nBins);

    // Loop over bins and extract content and error
    for (int i = 1; i <= prof->GetNbinsX(); ++i)
    {
        means.push_back(prof->GetBinContent(i)); // mean y in bin i
        errors.push_back(prof->GetBinError(i));  // standard error in bin i
    }

    // Clean up allocated profile to avoid memory leaks
    delete prof;

    return {means, errors};
}