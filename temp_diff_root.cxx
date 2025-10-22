#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>

void temperature_diff() {
    TString input_file = "smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.csv";
    TString output_root = "Temp_diff.root";
    std::ifstream infile(input_file.Data());
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open " << input_file << std::endl;
        return;
    }
    std::map<int, std::pair<double, double>> year_minmax; //year->(min, max)
    std::string line;
    while (std:: getline(infile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string year_str, month_str, day_str, temp_str;
        std::getline(ss, year_str, ',');
        std::getline(ss, month_str, ',');
        std::getline(ss, day_str, ',');
        std::getline(ss, temp_str, ',');
        if(year_str.empty() || temp_str.empty())
            continue;
        //year extraction
        int year = std::stoi(year_str);
        double temp = std::stod(temp_str);
        auto &entry = year_minmax[year];
        if (entry.first == 0 && entry.second == 0 && year_minmax.size() == 1) {
            entry = {temp, temp};
        } else {
            if (year_minmax[year].first == 0 && year_minmax[year].second == 0)
                year_minmax[year] = {temp, temp};
            else {
                if (temp < year_minmax[year].first) year_minmax[year].first = temp;
                if (temp > year_minmax[year].second) year_minmax[year].second = temp;
            }
        }
    }
    infile.close();
    // Create ROOT file and TTree
    TFile *fout = new TFile(output_root, "RECREATE");
    TTree *tree = new TTree("temperature_diff", "Yearly temperature differences");

    int year;
    double diff;

    tree->Branch("year", &year, "year/I");
    tree->Branch("difference", &diff, "difference/D");

    for (const auto &entry : year_minmax) {
        year = entry.first;
        diff = entry.second.second - entry.second.first;
        tree->Fill();
        std::cout << year << " -> dT = " << diff << "C" << std::endl;
    }

    tree->Write();
    fout->Close();

    std::cout << "Wrote results to " << output_root << std::endl;
}