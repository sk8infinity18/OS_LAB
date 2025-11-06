#!/bin/bash

arr=()
brr=()
for ((i=0; i<3; i++)); do
    arr+=($((i+1))) 
    done

for ((i=0; i<3; i++)); do
    if ((arr[i] % 2==0)); then
    echo even ${arr[i]}
    else
    echo odd ${arr[i]}; 
    fi
    done
    
echo ${arr[@]}    

for file in *txt; do
    brr+=($file)
    done
echo files are: ${brr[@]}

echo length of arr: ${#arr[@]}