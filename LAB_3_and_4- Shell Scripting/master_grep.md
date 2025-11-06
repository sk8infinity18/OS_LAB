🔹 Basic Search
grep "pattern" file              # Search for pattern in file
grep -i "pattern" file           # Case-insensitive search
grep -w "pattern" file           # Match whole word
grep -x "pattern" file           # Match entire line

🔹 Recursive Search
grep -r "pattern" .              # Search in current dir + subdirs
grep -R "pattern" .              # Same but follows symlinks
grep -rl "pattern" .             # List filenames with matches
grep -rL "pattern" .             # List filenames without matches

🔹 File Filtering
grep -r --include="*.txt" "pattern" .    # Search only in .txt files
grep -r --exclude="*.log" "pattern" .    # Exclude .log files
grep -r --exclude-dir="dir" "pattern" .  # Exclude directory

🔹 Counting
grep -c "pattern" file           # Count matching lines
grep -o "pattern" file | wc -l   # Count total matches

🔹 Context (Extra Lines)
grep -A 3 "pattern" file         # 3 lines After match
grep -B 3 "pattern" file         # 3 lines Before match
grep -C 2 "pattern" file         # 2 lines Before & After match

🔹 Output Formatting
grep -n "pattern" file           # Show line numbers
grep -b "pattern" file           # Show byte offset
grep --color=always "pattern" file   # Highlight matches

🔹 Regular Expressions
grep "^start" file               # Match lines starting with "start"
grep "end$" file                 # Match lines ending with "end"
grep "appl[ey]" file             # Match apple or apply
grep -E "cat|dog" file           # OR condition (extended regex)

🔹 Inverse Matching
grep -v "pattern" file           # Show lines NOT matching

🔹 Useful Combos
grep -r "TODO" . 2>/dev/null     # Recursive search, ignore errors
grep -rl "error" .               # Files containing "error"
grep -r --include="*.log" -o "error" . | wc -l   # Count "error" in logs


✅ Remember:

-r = recursive

-l = list filenames only

-c = count

-o = only matching parts

-n = line numbers

-v = invert match