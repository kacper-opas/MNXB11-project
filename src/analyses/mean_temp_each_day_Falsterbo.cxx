#include <string>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "include/analysis_utils.h"
#include "include/plotting_utils.h"
#include "include/analyses.h"

void mean_temp_each_day_Falsterbo()
{
    std::string falsterbo_tree =
        "datasets/root_trees/smhi-opendata_1_52230_20231007_155448_Falsterbo_preprocessed.root";

    TTree *tree = readTree(falsterbo_tree);
    TemperatureData data(tree);

    int nbins = 366;
    double xMin = 1;
    double xMax = 367;

    TProfile *prof = new TProfile("prof", "prof", nbins, xMin, xMax);
    for (size_t i = 0; i < data.temperatures.size(); ++i)
        prof->Fill(data.day_of_year[i], data.temperatures[i]);

    std::vector<double> means, errors;
    means.reserve(nbins);
    errors.reserve(nbins);

    for (int i = 1; i <= prof->GetNbinsX(); ++i)
    {
        if (prof->GetBinEntries(i) > 0)
        {
            means.push_back(prof->GetBinContent(i));
            errors.push_back(prof->GetBinError(i));
        }
        else
        {
            means.push_back(0.0);
            errors.push_back(0.0);
        }
    }

    delete prof;

    std::vector<double> x, ex;
    for (int i = 0; i < (int)means.size(); ++i)
    {
        x.push_back(i + 1);
        ex.push_back(0.0);
    }

    makeErrorGraph(x, means, ex, errors,
                   "Mean temperature on each day of the year in Falsterbo;Day of the year;Mean Temperature [Degrees Celsius]",
                   "results/mean_temp_each_day_Falsterbo.png");
}

