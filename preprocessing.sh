#!/bin/bash

#file that should be modified ORIGINAL WILL NOT BE CHAGED BY THIS CODE
Input_file="test10.csv"
#copy file in which the chages will be applied
Copy_file="${Input_file%.csv}_copy.csv"
#copying initial info into copyfile
cp "$Input_file" "$Copy_file"



#specifiy how many of the first lines should be deleted
Leading_lines=25

#deleting leading/ trailing whitespaces in each line
sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"


#deleting the first lines as specified and applying the changes to our input file
sed "1,${Leading_lines}d" "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"

#removing unnecessary columns
cut  --complement -d';' -f2,4 "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"


#replacing hyphens with commas in datetime object
#COMMENT if no comma separation in YYYY-MM-DD
awk -F';' 'gsub(/-/, ",", $1)' "$Copy_file" > temp.csv && mv temp.csv "$Copy_file"


#replacing leftover symbols with commas for proper csv formatting
sed -e 's/ /,/g' "$Copy_file"> temp.csv && mv temp.csv "$Copy_file"



