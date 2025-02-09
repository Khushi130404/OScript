#!/bin/bash

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
