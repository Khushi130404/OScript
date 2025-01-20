#!/bin/bash

echo -n "Enter the file name: "
read filename

if [ ! -f "$filename" ]; then
    echo "File not found!"
    exit 1
fi

line_count=$(wc -l < "$filename")

echo "Total lines in $filename: $line_count"
