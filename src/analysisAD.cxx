#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

void analysisAD() {
    std::string lulea_tree = "/home/andreadelic/git/MNXB11-project/datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";

    TFile *file = TFile::Open(lulea_tree.c_str(), "READ");
    TTree *tree = (TTree*)file->Get("tree");

    TCanvas *c1 = new TCanvas("c1", "January Temperatures", 800, 600);
    tree->Draw("temperature", "month==1", "hist");
}
