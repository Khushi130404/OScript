#!/bin/bash

THRESHOLD=80
EMAIL="khushipatel130404@gmail.com"  

df -h | awk 'NR>1 {print $5, $6}' | while read usage mount; do
    usage=${usage%\%}  
    if [ "$usage" -ge "$THRESHOLD" ]; then
        echo "WARNING: Disk usage on $mount is at $usage%" | mail -s "Disk Usage Alert" $EMAIL
    fi
done
