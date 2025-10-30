# Data preparation

-Extract the SMHI csv files and place them in datasets/raw
-Run the preprocessing via the wrapper script to preprocess all files 
``` sh
bash preprocessingwrapper.sh
```
# Compiling the code
The project uses C++17 and ROOT, in order to compile the code run
``` sh
make
```

-Convert the CSVs to ROOT files
``` sh
./write
```

To run the analysis simply execute
``` sh
./main
```
which runs all analyses and generates plots in the results directory.

