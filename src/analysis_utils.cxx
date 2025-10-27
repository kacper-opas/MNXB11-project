#include "include/analysis_utils.h"
#include "TFile.h"
#include "TProfile.h"

bool isLeapYear(int year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

int dayOfYear(int year, int month, int day)
{
    static const int daysBeforeMonthNormal[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    static const int daysBeforeMonthLeap[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

    if (isLeapYear(year))
    {
        return daysBeforeMonthLeap[month - 1] + day;
    }
    else
    {
        return daysBeforeMonthNormal[month - 1] + day;
    }
}

TTree *readTree(const std::string &tree_file)
{
    TFile *file = TFile::Open(tree_file.c_str(), "READ");
    TTree *tree = dynamic_cast<TTree *>(file->Get("tree"));

    return tree;
}

TemperatureData::TemperatureData() = default;

TemperatureData::~TemperatureData() = default;

TemperatureData::TemperatureData(TTree *tree)
{
    this->tree = tree;

    double year = 0, month = 0, day = 0, temp = 0;

    tree->SetBranchAddress("year", &year);
    tree->SetBranchAddress("month", &month);
    tree->SetBranchAddress("day", &day);
    tree->SetBranchAddress("temperature", &temp);

    Int_t nEntries = tree->GetEntries();
    years.reserve(nEntries);
    months.reserve(nEntries);
    days.reserve(nEntries);
    temperatures.reserve(nEntries);
    day_of_year.reserve(nEntries);

    for (Int_t i = 0; i < nEntries; ++i)
    {
        tree->GetEntry(i);
        years.push_back(year);
        months.push_back(month);
        days.push_back(day);
        temperatures.push_back(temp);

        day_of_year.push_back(dayOfYear(static_cast<int>(year),
                                        static_cast<int>(month),
                                        static_cast<int>(day)));
    }
}

std::pair<std::vector<double>, std::vector<double>>
TemperatureData::calculateMeanProfile(const std::string &y_var,
                                      const std::string &x_var,
                                      int nbins,
                                      double xMin,
                                      double xMax,
                                      const std::string &selection) const
{
    TProfile *prof = new TProfile("prof", "prof", nbins, xMin, xMax);

    std::string drawCmd = y_var + ":" + x_var + ">>prof";

    tree->Draw(drawCmd.c_str(), selection.c_str(), "goff");

    std::vector<double> means;
    std::vector<double> errors;
    means.reserve(nbins);
    errors.reserve(nbins);

    for (int i = 1; i <= prof->GetNbinsX(); ++i)
    {
        means.push_back(prof->GetBinContent(i));
        errors.push_back(prof->GetBinError(i));
    }

    delete prof;

    return {means, errors};
}
