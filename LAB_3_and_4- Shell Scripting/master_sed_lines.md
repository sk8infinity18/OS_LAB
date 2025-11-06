🔹 Print Lines
sed -n 'p' file            # Print all lines (like cat)
sed -n '5p' file           # Print 5th line
sed -n '2,4p' file         # Print lines 2 to 4
sed -n '/pattern/p' file   # Print lines matching "pattern"
sed -n '1~2p' file         # Print every 2nd line (1,3,5,…)

🔹 Delete Lines
sed '5d' file              # Delete 5th line
sed '2,4d' file            # Delete lines 2 to 4
sed '/pattern/d' file      # Delete lines containing "pattern"
sed '1~2d' file            # Delete every 2nd line
sed '2,$d' file            # Delete from 2nd line to end
sed '$d' file              # Delete last line

🔹 Insert & Append Lines
sed '2i\This is inserted' file   # Insert BEFORE line 2
sed '2a\This is appended' file   # Append AFTER line 2
sed '/pattern/i\Insert before' file  # Insert before pattern
sed '/pattern/a\Append after' file   # Append after pattern

🔹 Replace Lines
sed '3c\This is the new line' file   # Replace line 3
sed '/pattern/c\This line replaces matched line' file

🔹 Line Number Operations
sed -n '/pattern/=' file       # Print line numbers with "pattern"
nl file | sed '5!d'            # Show only line 5 with number

🔹 Start & End of File
sed '1i\New first line' file   # Insert at beginning
sed '$a\New last line' file    # Append at end
sed '1d' file                  # Delete first line
sed '$d' file                  # Delete last line


✅ Quick Notes:

i → insert before line

a → append after line

c → change line

d → delete line

p → print line

$ → last line

~N → every Nth line