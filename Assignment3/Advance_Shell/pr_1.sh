THRESHOLD=80
EMAIL="khushipatel130404@gmail.com"  

df -h | awk 'NR>1 {print $5, $6}' | while read usage mount; do
    usage=${usage%\%}  
    if [ "$usage" -ge "$THRESHOLD" ]; then
        echo "WARNING: Disk usage on $mount is at $usage%" | mail -s "Disk Usage Alert" $EMAIL
    fi
done

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Advance_Shell (Submission)  
# $ bash pr_1.sh  
# WARNING: Disk usage on / is at 85%  
# WARNING: Disk usage on /home is at 92%  
# WARNING: Disk usage on /var is at 88%  
