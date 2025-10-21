#include "TCanvas.h"
#include "TAxis.h"
#include "include/analysis_and_plotting.h"

int main() {
    TGraphErrors* graph = analysisKO();

    TCanvas* c1 = new TCanvas("c1", "Temperature Plot", 800, 600);
    graph->Draw("ALP");
    graph->GetXaxis()->SetLimits(0, 366);
    c1->Update();

    c1->SaveAs("temperature_plot.png");

    return 0;
}
