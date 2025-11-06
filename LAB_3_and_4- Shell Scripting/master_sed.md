🔹 Basic Usage
sed 's/old/new/' file            # Replace first occurrence per line
sed 's/old/new/g' file           # Replace all occurrences per line
sed -i 's/old/new/g' file        # Replace in file (in-place)
sed -i.bak 's/old/new/g' file    # Replace & keep backup as file.bak

🔹 Deletion
sed '/pattern/d' file            # Delete lines containing pattern
sed '2d' file                    # Delete 2nd line
sed '2,5d' file                  # Delete lines 2 to 5
sed '2,$d' file                  # Delete from line 2 to end
sed 'n;d' file                   # Delete every 2nd line
sed 'n;n;d' file                 # Delete every 3rd line

🔹 Print / Display
sed -n 'p' file                  # Print all lines (like cat)
sed -n '5p' file                 # Print 5th line only
sed -n '2,4p' file               # Print lines 2 to 4
sed -n '/pattern/p' file         # Print lines matching pattern

🔹 Insertion & Appending
sed '2i\This is inserted' file   # Insert before line 2
sed '2a\This is appended' file   # Append after line 2
sed '/pattern/i\Insert this' file # Insert before pattern
sed '/pattern/a\Append this' file # Append after pattern

🔹 Substitution (Advanced)
sed 's/old/new/2' file           # Replace 2nd occurrence only
sed 's/old/new/Ig' file          # Replace all, ignore case
sed 's/\<word\>//g' file         # Delete specific word
sed 's/[0-9]//g' file            # Remove all digits
sed 's/^/PREFIX: /' file         # Add prefix at line start
sed 's/$/ :SUFFIX/' file         # Add suffix at line end

🔹 Multiple Commands
sed -e 's/old/new/g' -e '/pattern/d' file

🔹 File Editing Tricks
sed -i '1i\New first line' file  # Insert at beginning of file
sed -i '$a\New last line' file   # Append at end of file
sed -n '1~2p' file               # Print every 2nd line
sed '1~2d' file                  # Delete every 2nd line

🔹 Useful Combos
sed -i 's/foo/bar/g' *.txt       # Replace in all .txt files
sed -n '/error/=' file           # Print line numbers with "error"
sed 's/^[ \t]*//;s/[ \t]*$//' file   # Trim leading/trailing spaces


✅ Remember:

s = substitute

d = delete

p = print

i = insert before

a = append after

-i = in-place editing

g = global (all matches in line)