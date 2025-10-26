#include "include/plotting_utils.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TBox.h"
#include "TStyle.h"
#include <iostream>

void makeBarPlot(const std::vector<double> &x,
                 const std::vector<double> &y,
                 const std::string &title,
                 const std::string &savePath)
{
    TCanvas *c = new TCanvas("c", title.c_str(), 1000, 600);

    double xmin = x.front();
    double xmax = x.back();
    double ymin = std::min(0.0, *std::min_element(y.begin(), y.end()));
    double ymax = std::max(0.0, *std::max_element(y.begin(), y.end()));

    TH1F *frame = c->DrawFrame(xmin, ymin, xmax, ymax);
    frame->SetTitle("plot");

    double barWidth = 0.6;
    for (size_t i = 0; i < x.size(); ++i)
    {
        TBox *bar = new TBox(x[i] - barWidth / 2, 0, x[i] + barWidth / 2, y[i]);
        bar->SetFillColor(y[i] > 0 ? kRed : kBlue);
        bar->Draw("same");
    }

    c->Update();
    c->SaveAs(savePath.c_str());
}

void makeHistogram()
{
}

void makeGraph()
{
}
