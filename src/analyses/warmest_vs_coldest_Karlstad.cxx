#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLine.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <numeric>
#include "include/analysis_and_plotting.h"
#include <TBox.h>

void warmest_vs_coldest_Karlstad() {
    const char *filename = "datasets/root_trees/smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.root";
    TFile *file = TFile::Open(filename, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return;
    }
    //climbing trees
    TTree *tree = (TTree*)file->Get("tree");
    if (!tree) {
        std::cerr << "Error: cannot find TTree 'tree' in file." << std::endl;
        file->Close();
        return;
    }
    Int_t year, month, day;
    Float_t temperature;
    tree->SetBranchAddress("year", &year);
    tree->SetBranchAddress("month", &month);
    tree->SetBranchAddress("day", &day);
    tree->SetBranchAddress("temperature", &temperature);
    std::map<int, std::vector<Float_t>> tempsByYear;
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        tempsByYear[year].push_back(temperature);
    }
    // Minmaxing year
    std::vector<int> years;
    std::vector<float> diffs;
    for (auto &entry : tempsByYear) {
        float minT = *std::min_element(entry.second.begin(), entry.second.end());
        float maxT = *std::max_element(entry.second.begin(), entry.second.end());
        years.push_back(entry.first);
        diffs.push_back(maxT - minT);
    }
    int nYears = years.size();
    // It is mean
    float meanAll = std::accumulate(diffs.begin(), diffs.end(), 0.0) / nYears;
    auto moving_mean = [&](int window) {
        std::vector<float> mm;
        for (int i = 0; i < nYears; i++) {
            int count = 0;
            float sum = 0;
            for (int j = std::max(0, i - window/2); j <= std::min(nYears-1, i + window/2); j++) {
                sum += diffs[j];
                count++;
            }
            mm.push_back(sum / count);
        }
        return mm;
    };
    std::vector<float> mm3 = moving_mean(3);
    std::vector<float> mm5 = moving_mean(5);
    // Look at this graph
    TCanvas *c1 = new TCanvas("c1", "Yearly Temperature Differences", 1000, 600);
    c1->SetGrid();
    TGraph *graphDiff = new TGraph(nYears);
    TGraph *graphMM3 = new TGraph(nYears);
    TGraph *graphMM5 = new TGraph(nYears);
    TLine *lineMean = new TLine(years.front(), meanAll, years.back(), meanAll);
    for (int i = 0; i < nYears; i++) {
        graphDiff->SetPoint(i, years[i], diffs[i]);
        graphMM3->SetPoint(i, years[i], mm3[i]);
        graphMM5->SetPoint(i, years[i], mm5[i]);
    }
    // spitting Bars
    graphDiff->SetLineColor(kBlue);
    graphDiff->SetLineWidth(2);
    graphMM3->SetLineColor(kMagenta);
    graphMM3->SetLineWidth(2);
    graphMM5->SetLineColor(kGreen+2);
    graphMM5->SetLineWidth(2);
    lineMean->SetLineColor(kBlack);
    lineMean->SetLineStyle(2);
    lineMean->SetLineWidth(2);
    // Do sht
    graphDiff->Draw("AP");
    for (int i = 0; i < nYears; i++) {
        float xLeft, xRight;
        if (i == 0) xLeft = years[i] - 0.5; 
        else xLeft = (years[i] + years[i-1]) / 2.0;
        if (i == nYears-1) xRight = years[i] + 0.5;
        else xRight = (years[i] + years[i+1]) / 2.0;
        float yTop = diffs[i];
        float yBottom = meanAll;
        TBox *bar;
        if (diffs[i] >= meanAll) {
            bar = new TBox(xLeft, yBottom, xRight, yTop);
            bar->SetFillColor(kRed);
        } else {
            bar = new TBox(xLeft, yTop, xRight, yBottom);
            bar->SetFillColor(kBlue);
        }
        bar->SetLineColor(kBlack);
        bar->Draw();
    }
    graphMM3->Draw("L SAME");
    graphMM5->Draw("L SAME");
    lineMean->Draw("SAME");
    graphDiff->GetXaxis()->SetTitle("Year");
    graphDiff->GetYaxis()->SetTitle("Temp Difference (#circC)");
    graphDiff->SetTitle("Yearly Temperature Differences with Moving Means");
    c1->SaveAs("yearly_temp_diff_bars.png");
    file->Close();
    std::cout << "Graph saved as 'yearly_temp_diff_bars.png'" << std::endl;
}