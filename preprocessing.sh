#!/bin/bash

# Default dataset directory
DATASET_DIR="datasets"

# Get input filename and optional number of leading lines
Input_file="$1"
Leading_lines="${2:-25}"

# Full path to input file inside dataset directory
Input_path="$DATASET_DIR/$Input_file"

# Create copy filename in same directory
Copy_file="${Input_path%.csv}_preprocessed.csv"
cp "$Input_path" "$Copy_file"

# Delete leading/trailing whitespace
sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Delete first N lines
sed "1,${Leading_lines}d" "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Remove unnecessary columns
cut --complement -d';' -f2,4 "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Replace hyphens with commas in datetime object
awk -F';' 'gsub(/-/, ",", $1)' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Replace leftover symbols with commas
sed -e 's/ /,/g' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Add column headers: year, month, day, temperature
sed -i '1i year,month,day,temperature' "$Copy_file"