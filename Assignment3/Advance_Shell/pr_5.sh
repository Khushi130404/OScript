LOGFILE="cpu_usage.log"

while true; do
    echo "$(date) - CPU Usage:" >> $LOGFILE
    top -b -n1 | grep "Cpu(s)" >> $LOGFILE
    echo "-----------------------------" >> $LOGFILE
    sleep 5
done

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Advance_Shell (Submission)
# $ bash pr_5.sh
# Sun Feb 09 14:35:10 IST 2025 - CPU Usage:
# %Cpu(s):  10.5 us,  2.3 sy,  0.0 ni, 85.9 id,  0.9 wa,  0.0 hi,  0.4 si,  0.0 st
# -----------------------------

# Sun Feb 09 14:35:15 IST 2025 - CPU Usage:
# %Cpu(s):   8.7 us,  1.9 sy,  0.0 ni, 88.2 id,  1.0 wa,  0.0 hi,  0.2 si,  0.0 st
# -----------------------------

# Sun Feb 09 14:35:20 IST 2025 - CPU Usage:
# %Cpu(s):  12.1 us,  3.0 sy,  0.0 ni, 82.6 id,  1.5 wa,  0.0 hi,  0.8 si,  0.0 st
# -----------------------------
