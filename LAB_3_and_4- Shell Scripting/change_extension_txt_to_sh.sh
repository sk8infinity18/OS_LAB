#!/bin/bash

echo Read dir name
read dir
if [[ -d $dir ]]; then
   
   find $dir -maxdepth 1 -type f -name "*.txt" | while read -r file ; do

   echo Renaming $file 
   base=${file%.txt}
   new=${base}.sh
   mv -- $file $new

   done

   else
   echo No .txt files exist
   fi