#!/bin/bash

# Default dataset directories
RAW_DATA_DIR="datasets/raw_data"
PREPROCESSED_DIR="datasets/preprocessed_data"

# Create preprocessed directory if it doesn't exist
mkdir -p "$PREPROCESSED_DIR"

# Get input filename and optional number of leading lines
Input_file="$1"
Leading_lines="${2:-25}"

# Full path to input file inside dataset directory
Input_path="$RAW_DATA_DIR/$Input_file"

# Create copy filename in preprocessed directory
Copy_file="$PREPROCESSED_DIR/${Input_file%.csv}_preprocessed.csv"
cp "$Input_path" "$Copy_file"

# Delete leading/trailing whitespace
sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Delete first N lines
sed "1,${Leading_lines}d" "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Remove unnecessary columns
cut --complement -d';' -f2,4 "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

awk -F';' '{
    sum[$1] += $2;    
    count[$1] += 1;   
}
END {
    for (date in sum) {
    avg = sum[date] / count[date];
    printf "%s;%.2f\n", date, avg;
        
    }
}' "$Copy_file" |sort > temp.csv && mv temp.csv "$Copy_file"

# Replace hyphens with commas in datetime object
awk -F';' 'gsub(/-/, ",", $1){print}' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

# Replace leftover spaces with commas
sed -e 's/ /,/g' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

