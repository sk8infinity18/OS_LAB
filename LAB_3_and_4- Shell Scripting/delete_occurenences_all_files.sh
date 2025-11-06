#!/bin/bash

# For current directory only
# for file in $(grep -low "AI" *); do
#     sed -i "s/\<AI\>//g" $file
#     done

# For a partcicular directory

echo enter dir name
read dir

if [[ ! -d $dir ]]; then 
    echo not a dir
    else
    
    grep -lw "AI" "$dir"/* | while IFS= read -r file; do 
        sed -i "s/\<AI\>//g" $file
        done
    fi