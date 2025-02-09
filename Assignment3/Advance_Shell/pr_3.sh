DIR=${1:-.}  
echo "Top 5 largest files in $DIR:"
find "$DIR" -type f -exec du -h {} + | sort -rh | head -n 5
