# Replace all occurences of a word with a new word
sed -i 's/AI/NAI/g' sample.txt  #if u dont want to permanently save it just omit '-i'

# do it in all files
sed -i 's/AI/NAI/g' *

# Delete a particular word
sed -i 's/\<AI\>//g' sample.txt

