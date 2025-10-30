#!/usr/bin/env bash

#exit when encountering errors
set -e

#declare the main script
MAIN_SCRIPT="./preprocessing.sh"

#list all the datafiles
DATAFILES=(datasets/raw_data/*)

#files that should be excluded from preprocessing
EXCLUDE="datasets/raw_data/datasets.tgz"

#looping over all files in the specified pash and executing the main script on them
for file in "${DATAFILES[@]}"; do

    if [[ "$file" == "$EXCLUDE" ]]; then
        continue
    fi

    base=$(basename "$file")

    "$MAIN_SCRIPT" "$base"

    
done

echo "All files preprocessed!"