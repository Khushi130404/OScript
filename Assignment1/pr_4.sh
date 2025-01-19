# Check if a name is File or Directory

echo "Enter File or Directory"
read f

if [ -f "$f" ]; then
    echo "$f is File"
elif [ -d "$f" ]; then
    echo "$f is Directory"
else
    echo "$f do not exist"
fi