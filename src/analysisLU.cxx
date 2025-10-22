#include <string>
#include <cmath>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
//#include "include/analysis_and_plotting.h"
#include <TDirectory.h>   
#include <TProfile.h>
#include <TFile.h>

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

    //DATAPROCESSING LULEA
    //using root draw with prof to get the mean average for each year
    ltree->Draw("temperature:year >> lavgtemp(12, 1990, 2000, 1000, -50, 50)", "", "prof");
    
    //storing the data from the histogramm
    TProfile *lavgtemp = (TProfile*)gDirectory->Get("lavgtemp");

    //from histogramm data get the number of bins 
    int nBins1 = lavgtemp->GetNbinsX();

    //extract average temperature with year for lulea
    for (int i = 1; i <= nBins1; ++i) {  // ROOT bins start at 1
        double lyear = lavgtemp->GetBinCenter(i);
        double lavgTemp = lavgtemp->GetBinContent(i);    // Average temperature in bin
        double lavgTempErr = lavgtemp->GetBinError(i);

    }



    //DATAPROCESSING FALSTERBO
    //drawing to avoid looping to get averages
    ftree->Draw("temperature:year >> favgtemp(12, 1990, 2000, 1000, -50, 50)", "", "prof");
    //storing the data from the histogramm
    TProfile *favgtemp = (TProfile*)gDirectory->Get("favgtemp");

    //from histogramm data get the number of bins 
    int nBins2 = favgtemp->GetNbinsX();

    //extract average temperature with year for lulea
    for (int i = 1; i <= nBins2; ++i) {  // ROOT bins start at 1
        double fyear = favgtemp->GetBinCenter(i);
        double favgTemp = favgtemp->GetBinContent(i);    // Average temperature in bin
        double favgTempErr = favgtemp->GetBinError(i);

    }

    if (nBins1 != nBins2 ) {
        std::cerr <<"Error, different amount of years analysed" << std::endl;
    }

    double difftemp;

    
}
