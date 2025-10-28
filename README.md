# Data preparation

-Extract the SMHI csv files and place them in datasets/raw
-Run the preprocessing scripts 
``` sh
bash preprocess.sh < filename.csv >
```
-Convert the CSVs to ROOT files
``` sh
write();
```

# Compiling the code
The project uses C++17 and ROOT, in order to compile the code run
``` sh
make
```
Which should generate an executable called "main"

# Usage
To run the analysis simply execute
``` sh
./main
```
which runs all analyses and generates plots in the results/ directory
