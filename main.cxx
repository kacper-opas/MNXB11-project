#include "include/analyses.h"
#include "include/analysis_utils.h"
#include "include/plotting_utils.h"

int main() {
    diff_in_mean_temp_Lulea_Falsterbo();
    mean_temp_each_day_Falsterbo();
    mean_temp_January_Lulea();
    warmest_day_Karlstad();
    warmest_vs_coldest_Karlstad();

    return 0;
}
