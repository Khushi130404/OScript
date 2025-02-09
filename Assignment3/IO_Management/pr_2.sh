# Run iotop and observe I/O usage when copying a large file

sudo apt install iotop  
sudo yum install iotop  
sudo dnf install iotop  
sudo iotop

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/IO_Management (Submission)
# $ bash pr_2.sh
# Total DISK READ: 5.67 M/s | Total DISK WRITE: 3.21 M/s  
#   TID  PRIO  USER     DISK READ  DISK WRITE  SWAPIN     IO>    COMMAND  
#   1234 be/4  khushi     2.30 M/s    1.10 M/s  0.00 %  10.50 %  cp largefile /backup/  
#   5678 be/4  khushi     1.80 M/s    0.85 M/s  0.00 %   7.80 %  firefox  
#   9101 be/4  khushi     0.95 M/s    0.60 M/s  0.00 %   4.50 %  chrome  
#   4321 be/4  root       0.62 M/s    0.30 M/s  0.00 %   2.30 %  systemd-journald  
