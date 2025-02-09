SOURCE_DIR="D:/OScript"  
BACKUP_DIR="/backup"
DATE=$(date +%F)
BACKUP_FILE="$BACKUP_DIR/backup-$DATE.tar.gz"
mkdir -p $BACKUP_DIR
tar -czf $BACKUP_FILE $SOURCE_DIR
echo "Backup saved at $BACKUP_FILE"

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Advance_Shell (Submission)
# $ bash pr_4.sh
# mkdir: cannot create directory ‘/backup’: Permission denied
# tar: Removing leading `D:/' from member names
# tar (child): /backup/backup-2025-02-09.tar.gz: Cannot open: No such file or directory
# tar (child): Error is not recoverable: exiting now
# tar: /backup/backup-2025-02-09.tar.gz: Cannot write: Broken pipe
# tar: Child returned status 2
# tar: Error is not recoverable: exiting now
# Backup saved at /backup/backup-2025-02-09.tar.gz