#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>
#include <map>
//#include "temperature_day.h"  // your class header

void convert_to_tree() {
    std::ifstream infile("smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.csv");

 TFile *outfile = new TFile("Karlstad_temperature.root", "RECREATE");
    TTree *tree = new TTree("tree", "Daily max temperatures for Karlstad");


    // --- Connect to class object branch
    temperature_day *p = nullptr;
    tree->SetBranchAddress("day", &p);

    Int_t N = tree->GetEntries();
    std::cout << "Entries: " << N << std::endl;

    // --- Data containers
    std::map<int, double> maxTempPerYear;
    std::map<int, int> warmestDayPerYear;

    // --- Loop over entries to find warmest day per year
    for (Int_t i = 0; i < N; ++i) {
        tree->GetEntry(i);

        int year = p->GetYear();
        int doy  = p->GetDayOfYear();
        double temp = p->GetTemperature();

        if (maxTempPerYear.find(year) == maxTempPerYear.end() || temp > maxTempPerYear[year]) {
            maxTempPerYear[year] = temp;
            warmestDayPerYear[year] = doy;
        }
    }

    // --- Create histogram
    TH1F *hWarmest = new TH1F("hWarmest",
        "Most Frequent Warmest Day of Year;Day of Year;Number of Years",
        365, 0.5, 365.5);

    for (const auto &entry : warmestDayPerYear)
        hWarmest->Fill(entry.second);

    // --- Draw
    TCanvas *c1 = new TCanvas("c1", "Warmest Day of Year", 800, 600);
    hWarmest->SetLineColor(kRed + 1);
    hWarmest->SetFillColorAlpha(kOrange - 2, 0.4);
    hWarmest->Draw();

    c1->SaveAs("warmest_days.png");

    file->Close();
}
