SOURCE_DIR="D:/OScript"  
BACKUP_DIR="/backup"
DATE=$(date +%F)
BACKUP_FILE="$BACKUP_DIR/backup-$DATE.tar.gz"
mkdir -p $BACKUP_DIR
tar -czf $BACKUP_FILE $SOURCE_DIR
echo "Backup saved at $BACKUP_FILE"
