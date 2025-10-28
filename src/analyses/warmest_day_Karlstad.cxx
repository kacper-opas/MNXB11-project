#include <string>
#include <vector>
#include <algorithm>
#include "TFile.h"
#include "TTree.h"
#include "include/analysis_utils.h"
#include "include/plotting_utils.h"
#include "include/analyses.h"

void warmest_day_Karlstad() {
    std::string filename = "datasets/root_trees/smhi-opendata_1_93220_20231007_155708_Karlstad_preprocessed.root";
    TTree* tree = readTree(filename);

    TemperatureData data(tree);

    std::vector<double> dayCounts(366, 0.0);

    std::vector<int> uniqueYears;
    for (double y : data.years) {
        int year = static_cast<int>(y);
        if (std::find(uniqueYears.begin(), uniqueYears.end(), year) == uniqueYears.end())
            uniqueYears.push_back(year);
    }

    for (int year : uniqueYears) {
        double maxTemp = -1e6;
        int maxDay = 1;

        for (size_t i = 0; i < data.years.size(); ++i) {
            if (static_cast<int>(data.years[i]) == year) {
                if (data.temperatures[i] > maxTemp) {
                    maxTemp = data.temperatures[i];
                    int month = static_cast<int>(data.months[i]);
                    int day   = static_cast<int>(data.days[i]);
                    maxDay = dayOfYear(year, month, day);
                }
            }
        }

        if (maxDay >= 1 && maxDay <= 366)
            dayCounts[maxDay - 1] += 1.0;
    }

    std::vector<double> days(366);
    for (int i = 0; i < 366; ++i) days[i] = i + 1;

    makeHistogram(days, dayCounts, "Warmest day in Karlstad;Day of the year;Counts", "results/warmest_day_Karlstad.png");
}
