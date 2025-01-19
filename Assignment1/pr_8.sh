# Count & Display File in given Directory

echo -n "Enter Directory : "
read dir

if [ -d "$dir" ]; then
    count=$(ls -1 "$dir" | wc -l)
    echo "Total Files : $count"
    ls -lA "$dir"
else   
    echo "Directory do not exist"
fi
