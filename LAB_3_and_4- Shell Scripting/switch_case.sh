#!/bin/bash


while true; do 
echo "Choose an option:"
echo "1. Say Hello"
echo "2. Show Date"
echo "3. Exit"
read choice
case $choice in
    1)
        echo "Hello!"
        ;;
    2)
        echo "Today's date is $(date)"
        ;;
    3)
        echo "Goodbye!"
        break;
        ;;
    *)
        echo "Invalid choice"
        ;;
esac
done