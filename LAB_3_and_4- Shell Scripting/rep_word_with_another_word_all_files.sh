#!/bin/bash

for file in $(grep -low "AI" *); do
    sed -i "s/AI/NAI/g" $file
    done