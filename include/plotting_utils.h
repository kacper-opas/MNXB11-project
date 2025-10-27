#pragma once

#include <vector>
#include <string>
#include <TGraphErrors.h>

void makeBarPlot(const std::vector<double> &x,
                 const std::vector<double> &y,
                 const std::string &title,
                 const std::string &savePath,
                 double baseY);

void makeHistogram(const std::vector<double> &x,
                   const std::vector<double> &y,
                   const std::string &title,
                   const std::string &savePath);

void makeErrorGraph(const std::vector<double> &x,
                    const std::vector<double> &y,
                    const std::vector<double> &ex,
                    const std::vector<double> &ey,
                    const std::string &title,
                    const std::string &savePath);