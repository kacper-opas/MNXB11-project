#include "include/plotting_utils.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TBox.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include <algorithm>
#include <iostream>

/**
 * @brief Draws a bar plot where each x-value has a bar extending from a base line (baseY) to y[i].
 *
 * Also overlays a running average trend line.
 */
void makeBarPlot(const std::vector<double> &x,
                 const std::vector<double> &y,
                 const std::string &title,
                 const std::string &savePath,
                 double baseY)
{
    TCanvas *c = new TCanvas("c", title.c_str(), 1000, 600);

    // Determine axis limits from data range.
    double xmin = x.front();
    double xmax = x.back();
    double ymin = std::min(baseY, *std::min_element(y.begin(), y.end()));
    double ymax = std::max(baseY, *std::max_element(y.begin(), y.end()));
    double margin = 0.1 * (ymax - ymin);
    ymin -= margin;
    ymax += margin;

    // Draw empty frame that sets axes and title.
    TH1F *frame = c->DrawFrame(xmin - 1, ymin, xmax + 1, ymax);
    frame->SetTitle(title.c_str());

    // Draw colored bars. Bars above baseY = red, below = blue.
    double barWidth = 0.6;
    for (size_t i = 0; i < x.size(); ++i)
    {
        double ylow  = std::min(baseY, y[i]);
        double yhigh = std::max(baseY, y[i]);

        TBox *bar = new TBox(x[i] - barWidth / 2, ylow,
                             x[i] + barWidth / 2, yhigh);
        bar->SetFillColor(y[i] > baseY ? kRed : kBlue);
        bar->Draw("same"); // Draw directly onto frame
    }

    // Compute running average trend line.
    std::vector<double> avg;
    avg.reserve(y.size());
    double cumulative = 0.0;

    for (size_t i = 0; i < y.size(); ++i)
    {
        cumulative += y[i];
        avg.push_back(cumulative / (i + 1)); // running mean
    }

    // Plot running average line
    TGraph *avgGraph = new TGraph(x.size(), x.data(), avg.data());
    avgGraph->SetLineColor(kBlack);
    avgGraph->SetLineWidth(1);
    avgGraph->Draw("L same");

    c->SaveAs(savePath.c_str());
}

/**
 * @brief Creates a simple histogram-like plot where bin centers come from `x` and bin heights from `y`.
 */
void makeHistogram(const std::vector<double> &x,
                   const std::vector<double> &y,
                   const std::string &title,
                   const std::string &savePath)
{
    TCanvas *c = new TCanvas("c", title.c_str(), 1200, 600);

    // Slightly extend axis range so bars are visually separated.
    double xmin = x.front() - 0.5;
    double xmax = x.back() + 0.5;

    // Create histogram with bins aligned to x values.
    TH1F *hist = new TH1F("hist", title.c_str(), x.size(), xmin, xmax);

    // Fill histogram: ROOT bins start at index 1.
    for (size_t i = 0; i < x.size(); ++i)
    {
        hist->SetBinContent(i + 1, y[i]);
    }

    hist->SetFillColor(kRed);
    hist->SetLineColor(kBlack);
    hist->Draw();

    c->SaveAs(savePath.c_str());
}

/**
 * @brief Creates a scatter plot with x/y uncertainties shown via error bars.
 */
void makeErrorGraph(const std::vector<double> &x,
                    const std::vector<double> &y,
                    const std::vector<double> &ex,
                    const std::vector<double> &ey,
                    const std::string &title,
                    const std::string &savePath)
{
    TCanvas *c = new TCanvas("c", title.c_str(), 1000, 600);

    // Determine plot bounds from data + padding
    double xmin = *std::min_element(x.begin(), x.end());
    double xmax = *std::max_element(x.begin(), x.end());
    double ymin = *std::min_element(y.begin(), y.end());
    double ymax = *std::max_element(y.begin(), y.end());
    double margin = 0.1 * (ymax - ymin);
    ymin -= margin;
    ymax += margin;

    // Draw axis frame
    TH1F *frame = c->DrawFrame(xmin - 1, ymin, xmax + 1, ymax);
    frame->SetTitle(title.c_str());

    // Construct graph with x/y errors
    TGraphErrors *graph = new TGraphErrors(x.size(),
                                           x.data(),
                                           y.data(),
                                           ex.data(),
                                           ey.data());

    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);

    graph->Draw("P same");

    c->SaveAs(savePath.c_str());
}