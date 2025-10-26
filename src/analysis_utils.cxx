#include "include/analysis_utils.h"
#include "TFile.h"
#include "TProfile.h"

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
    this->tree = tree; // save tree pointer

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

    for (Int_t i = 0; i < nEntries; ++i)
    {
        tree->GetEntry(i);
        years.push_back(year);
        months.push_back(month);
        days.push_back(day);
        temperatures.push_back(temp);
    }
}

std::vector<double> TemperatureData::calculateMeanProfile(const std::string &y_var,
                                                          const std::string &x_var,
                                                          int nbins,
                                                          double xMin,
                                                          double xMax,
                                                          const std::string &selection) const
{
    TProfile prof("prof", "prof", nbins, xMin, xMax);

    std::string drawCmd = y_var + ":" + x_var + ">>prof";
    tree->Draw(drawCmd.c_str(), selection.c_str(), "goff");

    std::vector<double> means;
    for (int i = 1; i <= prof.GetNbinsX(); ++i)
    {
        if (prof.GetBinEntries(i) > 0)
        {
            means.push_back(prof.GetBinContent(i));
        }
    }

    return means;
}
