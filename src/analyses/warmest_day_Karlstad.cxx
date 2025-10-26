#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "TGraph.h"
#include "include/analysis_and_plotting.h"

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int dayOfYear(int year, int month, int day) {
    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (isLeapYear(year)) days_in_month[1] = 29;
    int doy = 0;
    for (int i = 0; i < month - 1; i++) doy += days_in_month[i];
    doy += day;
    return doy;
}

void warmest_day_Karlstad()
{
    std::string karlstadt_tree = "datasets/root_trees/smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.root";
    TFile *file = TFile::Open(karlstadt_tree.c_str(), "READ");
    TTree *tree = (TTree*)file->Get("tree");

    int year, month, day;
    float temperature;
    tree->SetBranchAddress("year", &year);
    tree->SetBranchAddress("month", &month);
    tree->SetBranchAddress("day", &day);
    tree->SetBranchAddress("temperature", &temperature);

    Int_t N = tree->GetEntries();

    std::vector<int> years;
    std::vector<double> maxTemps;
    std::vector<int> warmestDays;

    for (Int_t i = 0; i < N; ++i) {
        tree->GetEntry(i);
        int doy = dayOfYear(year, month, day);

        bool found = false;
        for (size_t j = 0; j < years.size(); ++j) {
            if (years[j] == year) {
                found = true;
                if (temperature > maxTemps[j]) {
                    maxTemps[j] = temperature;
                    warmestDays[j] = doy;
                }
                break;
            }
        }

        if (!found) {
            years.push_back(year);
            maxTemps.push_back(temperature);
            warmestDays.push_back(doy);
        }
    }

    TH1F *hWarmest = new TH1F("hWarmest",
        "Most Frequent Warmest Day of Year;Day of Year;Number of Years",
        365, 0.5, 365.5);

    for (size_t i = 0; i < warmestDays.size(); ++i)
        hWarmest->Fill(warmestDays[i]);

    TCanvas *c1 = new TCanvas("c1", "Warmest Day of Year", 800, 600);
    hWarmest->SetLineColor(kRed + 1);
    hWarmest->SetFillColorAlpha(kOrange - 2, 0.4);
    hWarmest->Draw();

    c1->SaveAs("warmest_days.png");
    file->Close();
}
