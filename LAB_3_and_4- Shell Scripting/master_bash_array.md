#!/bin/bash

# 1. Array Declaration
arr=(10 2 34 3 1 67)

# 2. Length of array
echo "Length = ${#arr[@]}"

# 3. Accessing elements
echo "First element = ${arr[0]}"
echo "Last element  = ${arr[-1]}"   # works in bash 4.3+

# 4. Print all elements
echo "All elements = ${arr[@]}"

# 5. Loop (index-based)
echo "Index-based loop:"
for ((i=0; i<${#arr[@]}; i++)); do
    echo "Index $i -> ${arr[i]}"
done

# 6. Loop (foreach style)
echo "Foreach loop:"
for val in "${arr[@]}"; do
    echo "Value -> $val"
done

# 7. Append element
arr+=(99)
echo "After append = ${arr[@]}"

# 8. Insert / Update element
arr[2]=500
echo "After update index 2 = ${arr[@]}"

# 9. Delete element
unset arr[3]
echo "After deletion = ${arr[@]}"

# 10. Search for an element
search=34
found=0
for val in "${arr[@]}"; do
    if [[ $val -eq $search ]]; then
        found=1
        break
    fi
done
[[ $found -eq 1 ]] && echo "$search found" || echo "$search not found"

# 11. Even / Odd separation
echo "Even numbers:"
for val in "${arr[@]}"; do
    if (( val % 2 == 0 )); then
        echo $val
    fi
done

echo "Odd numbers:"
for val in "${arr[@]}"; do
    if (( val % 2 != 0 )); then
        echo $val
    fi
done

# 12. Sum of elements
sum=0
for val in "${arr[@]}"; do
    (( sum += val ))
done
echo "Sum = $sum"

# 13. Maximum element
max=${arr[0]}
for val in "${arr[@]}"; do
    (( val > max )) && max=$val
done
echo "Max = $max"

# 14. Minimum element
min=${arr[0]}
for val in "${arr[@]}"; do
    (( val < min )) && min=$val
done
echo "Min = $min"

# 15. Sort array (ascending)
sorted=($(for val in "${arr[@]}"; do echo $val; done | sort -n))
echo "Sorted (asc) = ${sorted[@]}"

# 16. Sort array (descending)
sorted_desc=($(for val in "${arr[@]}"; do echo $val; done | sort -nr))
echo "Sorted (desc) = ${sorted_desc[@]}"

# 17. Reverse array (manual loop)
reversed=()
for ((i=${#arr[@]}-1; i>=0; i--)); do
    reversed+=("${arr[i]}")
done
echo "Reversed = ${reversed[@]}"
