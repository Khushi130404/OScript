# Display Name of files with less than 10% free space

df -h | awk '$5+0 >= 90 {print $1, $6}'