# Create Backup Script

echo -n "Enter Directory : "
read dir

if [ -d "$dir" ]; then
timestamp=$(date +"%Y%m%d%H%M%S")
    backup_dir="backup_$timestamp"
    cp -r "$dir" "$backup_dir"
    if [ $? -eq 0 ]; then
        echo "Backup of '$dir' was successful. Backup saved as '$backup_dir'."
    else
        echo "Backup failed."
    fi
else
    echo "Directory do not exist"
fi