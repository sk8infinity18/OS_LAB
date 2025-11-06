#!/bin/bash

# list all files (only file names) containing the input pattern (string) in the folder entered by the user

echo Enter file
read file

for f in $file*; do
    if [ -f $f ]; then
    echo $f
fi
done