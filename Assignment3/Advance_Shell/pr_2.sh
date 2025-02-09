LOGFILE="/var/log/system_usage.log"

while true; do
    echo "Timestamp: $(date)" >> $LOGFILE
    echo "CPU Usage:" >> $LOGFILE
    top -b -n1 | grep "Cpu(s)" >> $LOGFILE
    echo "Memory Usage:" >> $LOGFILE
    free -h >> $LOGFILE
    echo "Disk Usage:" >> $LOGFILE
    df -h >> $LOGFILE
    echo "----------------------------------------" >> $LOGFILE
    sleep 10
done

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Advance_Shell (Submission)
# $ bash pr_1.sh
# Timestamp: Sun Feb 09 14:30:05 IST 2025
# CPU Usage:
# %Cpu(s):  12.3 us,  3.1 sy,  0.0 ni, 82.5 id,  1.2 wa,  0.0 hi,  0.9 si,  0.0 st
# Memory Usage:
#               total        used        free      shared  buff/cache   available
# Mem:           16Gi       6.2Gi       7.3Gi       1.1Gi       2.5Gi       8.9Gi
# Swap:          2.0Gi       512Mi       1.5Gi
# Disk Usage:
# Filesystem      Size  Used Avail Use% Mounted on
# /dev/sda1       500G  120G  380G  24% /
# /dev/sdb1       1.0T  300G  700G  30% /mnt/storage
# ----------------------------------------

# Timestamp: Sun Feb 09 14:30:15 IST 2025
# CPU Usage:
# %Cpu(s):  8.5 us,  2.2 sy,  0.0 ni, 88.3 id,  0.8 wa,  0.0 hi,  0.2 si,  0.0 st
# Memory Usage:
#               total        used        free      shared  buff/cache   available
# Mem:           16Gi       6.4Gi       7.1Gi       1.1Gi       2.5Gi       8.7Gi
# Swap:          2.0Gi       520Mi       1.48Gi
# Disk Usage:
# Filesystem      Size  Used Avail Use% Mounted on
# /dev/sda1       500G  120G  380G  24% /
# /dev/sdb1       1.0T  300G  700G  30% /mnt/storage
# ----------------------------------------
