#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
//#include "include/analysis_and_plotting.h"
#include <TDirectory.h>   
#include <TProfile.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>

void analysisLU()
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

    //reading the branches with temperatures and year numbers for both trees 
    int lyear, fyear;
    float ltemp, ftemp;
    ltree->SetBranchAddress("year", &lyear);
    ltree->SetBranchAddress("temperature", &ltemp);
    ftree->SetBranchAddress("year", &fyear);
    ftree->SetBranchAddress("temperature", &ftemp);

    //initialize and get number of entries for each tree 
    Int_t lnentries = ltree->GetEntries();
    Int_t fentries = ftree->GetEntries();

    //set starting and ending years for our plot
    int startyear = 1950;
    int endyear = 2022;
    int yearbins = endyear - startyear + 1; 

    //build string from components
    std::string cmd = "temperature:year >> lavgtemp(" + std::to_string(yearbins) + "," + std::to_string(startyear) + "," + std::to_string(endyear) + ", 1000, -50, 50)";


    //DATAPROCESSING LULEA
    //using root draw with prof to get the mean average for each year
    ltree->Draw(cmd.c_str(), "", "prof");
    
    //storing the data from the histogramm
    TProfile *lavgtemp = (TProfile*)gDirectory->Get("lavgtemp");

    //from histogramm data get the number of bins 
    int nBins1 = lavgtemp->GetNbinsX();

    //define vectors so we can store all the values 
    std::vector<double> lyears;
    std::vector<double> lavgTemps;
    std::vector<double> lavgTempErrs;
    //extract average temperature with year for lulea
    for (int i = 1; i <= nBins1; ++i) {  
        lyears.push_back(lavgtemp->GetBinCenter(i));
        lavgTemps.push_back(lavgtemp->GetBinContent(i));   
        lavgTempErrs.push_back(lavgtemp->GetBinError(i));

    }



    //DATAPROCESSING FALSTERBO
    //string for input 
    std::string cmd2 = "temperature:year >> favgtemp(" + std::to_string(yearbins) + "," + std::to_string(startyear) + "," + std::to_string(endyear) + ", 1000, -50, 50)";

    //drawing to avoid looping to get averages
    ftree->Draw(cmd2.c_str(), "", "prof");
    //storing the data from the histogramm
    TProfile *favgtemp = (TProfile*)gDirectory->Get("favgtemp");

    //checking if the histogram for falsterbo is created properly
    if (!favgtemp) {
    std::cerr << "Error: Histogram 'favgtemp' not found in current directory!" << std::endl;
    return; 
}
    //from histogramm data get the number of bins 
    int nBins2 = favgtemp->GetNbinsX();

    //extract average temperature with year for falsterbo
    std::vector<double> fyears;
    std::vector<double> favgTemps;
    std::vector<double> favgTempErrs;
    
    for (int i = 1; i <= nBins2; ++i) {  
        fyears.push_back(favgtemp->GetBinCenter(i));
        favgTemps.push_back(favgtemp->GetBinContent(i));   
        favgTempErrs.push_back(favgtemp->GetBinError(i));

    }

    if (nBins1 != nBins2 ) {
        std::cerr <<"Error, different amount of years analysed" << std::endl;
    }

    
    std::vector<double> difftemp;

    for (int i = 1; i <= nBins2; ++i) {
        difftemp.push_back(favgTemps[i] - lavgTemps[i]);
    }

    //GRAPHING
   
    int nYears = fyears.size();
double start = fyears.front() - 0.5;
double end   = fyears.back() + 0.5;

// Make a histogram with one bin per year
TH1D *hdiff = new TH1D("hdiff", "Average Temperature Difference per Year;Year;ΔT (°C)",
                       nYears, start, end);

// Fill the bins manually
for (size_t i = 0; i < fyears.size(); ++i) {
    hdiff->SetBinContent(i+1, difftemp[i]);  // +1 because ROOT bins start at 1
}

// Optional: style
hdiff->SetLineColor(kBlue+1);
hdiff->SetFillColorAlpha(kAzure-9, 0.4);
hdiff->SetLineWidth(2);

TCanvas *c2 = new TCanvas("c2", "Histogram of ΔT", 900, 600);
hdiff->Draw("HIST");

c2->SaveAs("temp_difference_histogram.png"); 
}
