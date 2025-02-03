# Search for files modified within the last 7 days using find.

find D:/ -type f -mtime -7 -exec ls -lh {} \;
