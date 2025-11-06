#!/bin/bash

#Check whether its a file or dir
echo Enter name:
read name 

if [ -d $name ]; then
    echo Its a directory
elif [ -f $name ] ; then
    echo Its a file
else
    echo Nothing was found
fi    