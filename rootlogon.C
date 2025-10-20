
#include <TStyle.h>

#include <iostream>
void rootlogon() {
  // Add any code here you want to run automatically when you launch ROOT. Here
  // are some example style settings you can use!
  std::cout << "This output comes from the rootlogon.C macro which ROOT will "
               "run automatically on startup!"
            << std::endl;
  gStyle->SetOptStat(
      0);  // Let's make our plots look a bit better. Get rid of the stat box
  gStyle->SetOptTitle(
      0);  // Get rid of the title (good plots use legends instead)
  gStyle->SetTitleSize(0.05, "x");  // Use bigger text on the axes
  gStyle->SetTitleSize(0.05, "y");
  gStyle->SetLabelSize(0.05, "x");  // Use bigger labels too
  gStyle->SetLabelSize(0.05, "y");
  gStyle->SetPadTopMargin(0.05);  // Change the margins to fit our new sizes
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.16);
}
