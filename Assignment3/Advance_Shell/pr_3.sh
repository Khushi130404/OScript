DIR=${1:-.}  
echo "Top 5 largest files in $DIR:"
find "$DIR" -type f -exec du -h {} + | sort -rh | head -n 5

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Advance_Shell (Submission)
# $ bash pr_3.sh
# Top 5 largest files in .:
# 8.0K    ./cpu_usage.log
# 4.0K    ./pr_2.sh
# 1.0K    ./pr_5.sh
# 1.0K    ./pr_4.sh
# 1.0K    ./pr_3.sh