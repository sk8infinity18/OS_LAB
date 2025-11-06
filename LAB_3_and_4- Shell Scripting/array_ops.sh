#!/bin/bash

arr=("$@")
brr=()
sum=0
for((i=0; i< ${#arr[@]} ; i++)) do
    sum=$((sum + arr[i]))
    brr+=(${arr[i]})
    done

avg=$(echo " scale=2; ($sum / ${#arr[@]})" | bc)
echo $avg
echo ${brr[@]}