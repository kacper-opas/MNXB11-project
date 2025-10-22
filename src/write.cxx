#include <TFile.h>
#include <TTree.h>
#include <filesystem>
#include <string>

void write() {
    std::string input_dir = "datasets/preprocessed_data";
    std::string output_dir = "datasets/root_trees";

    // Loop over all CSV files in the input directory
    for (const auto& entry : std::filesystem::directory_iterator(input_dir)) {
        std::string csv_file = entry.path().string();
        std::string base_name = entry.path().stem().string();
        std::string root_file_path = output_dir + "/" + base_name + ".root";

        // Open ROOT file for writing
        TFile f(root_file_path.c_str(), "RECREATE");

        // Create a TTree
        TTree t("tree", ("Tree from " + base_name).c_str());

        t.ReadFile(csv_file.c_str(), "year/I:month/I:day/I:temperature/F", ',');

        // Write and close
        t.Write();
        f.Close();
    }
}
