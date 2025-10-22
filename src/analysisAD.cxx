#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TStyle.h"

void analysisAD() {
    std::string lulea_tree = "/home/andreadelic/git/MNXB11-project/datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";

    TFile *file = TFile::Open(lulea_tree.c_str(), "READ");
    TTree *tree = (TTree*)file->Get("tree");

    TCanvas *c1 = new TCanvas("c1", "Average January Temperatures", 800, 600);
    gStyle->SetOptStat(1111); // toggle statistics box

    TProfile *prof = new TProfile("prof", "Average January Temperatures", 75, 1949, 2024);

    tree->Draw("temperature:year>>prof", "month==1");

    prof->SetFillColor(kBlue);
    prof->SetLineColor(kBlue);
    prof->SetMarkerStyle(20); 
    prof->SetLineWidth(2);

    prof->GetXaxis()->SetTitle("Year");
    prof->GetYaxis()->SetTitle("Average January Temperature (°C)");

    prof->GetYaxis()->SetRangeUser(-25, 0);

    prof->Draw("hist");

    c1->Update();
}