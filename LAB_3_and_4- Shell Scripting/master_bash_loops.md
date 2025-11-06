#!/bin/bash

# -----------------------------
# 1. For Loop (Classic C-style)
# -----------------------------
echo "C-style For Loop:"
for ((i=1; i<=5; i++)); do
    echo "i = $i"
done

# -----------------------------
# 2. For Loop (List Iteration)
# -----------------------------
echo "For Loop over list:"
for val in 10 20 30 40; do
    echo "val = $val"
done

# -----------------------------
# 3. For Loop (Array Iteration)
# -----------------------------
arr=(5 15 25 35)
echo "Array iteration:"
for val in "${arr[@]}"; do
    echo "val = $val"
done

# With index
for ((i=0; i<${#arr[@]}; i++)); do
    echo "arr[$i] = ${arr[i]}"
done

# -----------------------------
# 4. While Loop
# -----------------------------
echo "While Loop:"
count=1
while [ $count -le 5 ]; do
    echo "count = $count"
    ((count++))
done

# -----------------------------
# 5. Until Loop
# -----------------------------
echo "Until Loop:"
n=1
until [ $n -gt 5 ]; do
    echo "n = $n"
    ((n++))
done

# -----------------------------
# 6. Loop with break & continue
# -----------------------------
echo "Break and Continue Example:"
for ((i=1; i<=10; i++)); do
    if (( i == 3 )); then
        echo "Skipping 3"
        continue
    fi
    if (( i == 7 )); then
        echo "Breaking at 7"
        break
    fi
    echo "i = $i"
done

# -----------------------------
# 7. Reading from a file line by line
# -----------------------------
# (assuming file.txt exists)
echo "Reading from file:"
while read -r line; do
    echo "Line: $line"
done < file.txt

# -----------------------------
# 8. Infinite Loop (use Ctrl+C to stop)
# -----------------------------
# echo "Infinite loop:"
# while true; do
#     echo "Press Ctrl+C to stop"
#     sleep 1
# done
