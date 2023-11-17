#!/bin/bash

file_path="esp32.txt"
response="OK"

# Create the file if it doesn't exist
touch "$file_path"

while true; do
    # Use inotifywait to wait for changes in the file
    inotifywait -e modify "$file_path" 2>/dev/null

    # Check if a new line is written to the file
    if [[ $(tail -n 1 "$file_path" | cut -c 1-2) == "AT" ]]; then
        # Append "OK" to the file
        echo "$response" > "$file_path"
    fi
done
