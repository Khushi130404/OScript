# start /HIGH notepad.exe
# tasklist | findstr notepad
# wmic process where ProcessId=910 call setpriority 128
# (Get-Process -Id 910).PriorityClass = "High"

nice -n 10 sleep 10 &
renice -n -5 -p 910

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Process_Management (Submission)
# $ bash pr_3.sh
# [1] 910
# 910 (process ID) old priority 10, new priority -5
