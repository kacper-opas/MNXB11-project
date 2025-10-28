#pragma once

#include <vector>
#include <string>

/**
 * @brief Draws a bar plot where each x-value corresponds to a bar from baseY to y[i],
 *        and overlays a running average trend line.
 *
 * @param x        X-axis positions for each bar.
 * @param y        Bar heights (values).
 * @param title    Plot title.
 * @param savePath Output file path (e.g. "plot.png").
 * @param baseY    Baseline reference value from which bars extend.
 */
void makeBarPlot(const std::vector<double> &x,
                 const std::vector<double> &y,
                 const std::string &title,
                 const std::string &savePath,
                 double baseY = 0.0);

/**
 * @brief Draws a histogram-style bar chart where x values define the bin centers
 *        and y values define the bin heights.
 *
 * @param x        Bin center positions.
 * @param y        Bin values (heights).
 * @param title    Plot title.
 * @param savePath Output file path (e.g. "plot.png").
 */
void makeHistogram(const std::vector<double> &x,
                   const std::vector<double> &y,
                   const std::string &title,
                   const std::string &savePath);

/**
 * @brief Draws a scatter plot with symmetric or asymmetric x/y error bars.
 *
 * @param x        X-values.
 * @param y        Y-values.
 * @param ex       X uncertainties (error bar half-widths).
 * @param ey       Y uncertainties.
 * @param title    Plot title.
 * @param savePath Output file path.
 */
void makeErrorGraph(const std::vector<double> &x,
                    const std::vector<double> &y,
                    const std::vector<double> &ex,
                    const std::vector<double> &ey,
                    const std::string &title,
                    const std::string &savePath);