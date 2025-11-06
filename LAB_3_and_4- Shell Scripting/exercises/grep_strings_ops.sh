# Find all occurences of a 'string' in a file
grep "word" file.txt

# Find all occurences of a word in a file
grep -w "word" file.txt

# Find all occurences of a word in a file (case - insensitive)
grep -iw "word" file.txt

# USEFUL
# Print the particular word the no of times it occured
grep -ow "AI" sample.txt

# Print its frequency of that word
grep -ow "AI" sample.txt | wc -l

# Search all the files in the current directory for a particular word
grep -l "AI" *


# Search all the files in the current directory AND SUBFOLDERS for a particular word
grep -rl "AI" .