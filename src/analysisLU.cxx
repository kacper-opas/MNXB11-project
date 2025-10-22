#include <string>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
//#include "include/analysis_and_plotting.h"
#include <TDirectory.h>   
#include <TProfile.h>
#include <TFile.h>
#include <ROOT/RDataFrame.hxx>

TGraph analysisLU()
{
    //assigning strings to root object pash"
    std::string falsterbo_tree = "datasets/root_trees/smhi-opendata_1_52230_20231007_155448_Falsterbo_preprocessed.root";
    std::string lule_tree = "datasets/root_trees/smhi-opendata_1_162860_20231007_155220_Lulea_preprocessed.root";
    
    //reading the file for falsterbo
    TFile *ffile = TFile::Open(falsterbo_tree.c_str(), "READ");
    TTree *ftree = (TTree*)ffile->Get("tree");

    //reading the file for lulea
    TFile *lfile = TFile::Open(lule_tree.c_str(), "READ");
    TTree *ltree = (TTree*)lfile->Get("tree");

ROOT::RDataFrame ldf(*ltree);
ROOT::RDataFrame fdf(*ftree);

// Compute average temperature per year for each tree
auto l_avg = ldf.GroupBy("year").Mean("temperature");
auto f_avg = fdf.GroupBy("year").Mean("temperature");

// Convert grouped results to a map for easy lookup
std::map<int, double> l_map;
std::map<int, double> f_map;

l_avg->Foreach([&](int year, double temp_mean) {
    l_map[year] = temp_mean;
}, {"year", "temperature"});

f_avg->Foreach([&](int year, double temp_mean) {
    f_map[year] = temp_mean;
}, {"year", "temperature"});

// Now compute differences
std::vector<int> years;
std::vector<double> diffs;

for (const auto& [year, ltemp] : l_map) {
    if (f_map.count(year)) {
        years.push_back(year);
        diffs.push_back(ltemp - f_map[year]);
    }
}

// Plot differences as a TGraph
TGraph *gr = new TGraph(years.size(), years.data(), diffs.data());
gr->SetTitle("Average Temperature Difference per Year");
gr->GetXaxis()->SetTitle("Year");
gr->GetYaxis()->SetTitle("ltree - ftree temperature");
gr->Draw("AL");

    


}
