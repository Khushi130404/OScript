LOGFILE="cpu_usage.log"

while true; do
    echo "$(date) - CPU Usage:" >> $LOGFILE
    top -b -n1 | grep "Cpu(s)" >> $LOGFILE
    echo "-----------------------------" >> $LOGFILE
    sleep 5
done
