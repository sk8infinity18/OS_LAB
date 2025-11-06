#!/bin/bash

# Replace all files with .txt extension with .text in the current directory.
# This has to be done recursively i.e if the current folder contains a folder
# "OS" with abc.txt then it has to be changed to abc.text

# Finds the files in the current directory and nested directories too
find . -type f  # NOTE: there is no -maxdepth 1
echo

# Find files only in the current folder
echo Files in current folder
find . -maxdepth 1 -type f 
echo 

# Find all the files with a particular name or extension
echo case sensitive match
find . -maxdepth 1 -type f -name "*o*" 
echo

echo case insensitive match 
find . -maxdepth 1 -type f -iname "*o*"   #same result if u do "*O*"
echo

echo files with .txt extension
find . -type f -name "*.txt" 

