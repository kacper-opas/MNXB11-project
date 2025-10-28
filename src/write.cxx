#include <TFile.h>
#include <TTree.h>
#include <filesystem>
#include <string>

/**
 * @brief Converts all CSV files in `datasets/preprocessed_data` into ROOT files
 *        containing a TTree named "tree" with branches:
 *        year, month, day, temperature.
 *
 * Output ROOT files are written to `datasets/root_trees` with the same base name.
 */
void write()
{
    const std::string inputDir  = "datasets/preprocessed_data";
    const std::string outputDir = "datasets/root_trees";

    // Iterate over all files in input directory
    for (const auto& entry : std::filesystem::directory_iterator(inputDir))
    {
        // Full path to input CSV file
        std::string csvPath = entry.path().string();

        // File name without extension (e.g., "data_1990")
        std::string baseName = entry.path().stem().string();

        // Destination ROOT file path
        std::string rootPath = outputDir + "/" + baseName + ".root";

        // Create ROOT file (overwrites if exists)
        TFile rootFile(rootPath.c_str(), "RECREATE");

        // Create a TTree with a descriptive title
        TTree tree("tree", ("Tree from " + baseName).c_str());

        //Read CSV directly into TTree
        tree.ReadFile(csvPath.c_str(), "year/D:month/D:day/D:temperature/D", ',');

        // Write tree to file and close
        tree.Write();
        rootFile.Close();
    }
}