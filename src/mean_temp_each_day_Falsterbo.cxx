#include <string>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "include/analysis_and_plotting.h"

void mean_temp_each_day_Falsterbo()
{
    std::string falsterbo_tree = "datasets/root_trees/smhi-opendata_1_52230_20231007_155448_Falsterbo_preprocessed.root";

    TFile *file = TFile::Open(falsterbo_tree.c_str(), "READ");
    TTree *tree = (TTree*)file->Get("tree");

    int year, month, day;
    float temperature;
    tree->SetBranchAddress("year", &year);
    tree->SetBranchAddress("month", &month);
    tree->SetBranchAddress("day", &day);
    tree->SetBranchAddress("temperature", &temperature);

    double tempSum[366] = {0};
    double tempSum2[366] = {0};
    int tempCount[366] = {0};

    Int_t nentries = tree->GetEntries();
    for (Int_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        int doy = dayOfYear(year, month, day) - 1;
        tempSum[doy] += temperature;
        tempSum2[doy] += temperature * temperature;
        tempCount[doy]++;
    }

    double x[366], y[366], ex[366], ey[366];
    int points = 0;
    for (int i = 0; i < 366; i++) {
        if (tempCount[i] > 0) {
            x[points] = i + 1;
            y[points] = tempSum[i] / tempCount[i];
            ex[points] = 0;
            ey[points] = sqrt(tempSum2[i] / tempCount[i] - y[points] * y[points]);
            points++;
        }
    }

    TGraphErrors *graph = new TGraphErrors(points, x, y, ex, ey);
    graph->Draw("APL"); 

    file->Close();
}
