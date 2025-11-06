#!/bin/bash

echo enter base and ta
read base ta

ga=$(echo "$base + $ta + (0.1*$base)" | bc)

echo $ga