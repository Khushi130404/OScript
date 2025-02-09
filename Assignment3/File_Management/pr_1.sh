# Create a directory structure with specific permissions.

mkdir -p /project/{src,bin,logs,config}
ls -R /project
chmod 755 /project
chmod 700 /project/logs
chmod 770 /project/config
chown user1:developers /project -R
ls -l /project
stat /project/config

touch /project/src/main.c
mkdir /project/src/modules

cp /project/src/main.c /project/bin/
mv /project/bin/main.c /project/src/

ln /project/src/main.c /project/src/main_hardlink.c  
ln -s /project/src/main.c /project/src/main_symlink  

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/File_Management (Submission)
# $ bash pr_1.sh

# /project:
# bin  config  logs  src  

# /project/bin:

# /project/config:

# /project/logs:

# /project/src:
# main.c  main_hardlink.c  main_symlink  modules  

# total 4
# drwxr-xr-x 4 user1 developers 4096 Feb  9 12:00 .
# drwxr-xr-x 4 user1 developers 4096 Feb  9 12:00 ..
# drwxr-xr-x 2 user1 developers 4096 Feb  9 12:00 bin
# drwxrwx--- 2 user1 developers 4096 Feb  9 12:00 config
# drwx------ 2 user1 developers 4096 Feb  9 12:00 logs
# drwxr-xr-x 3 user1 developers 4096 Feb  9 12:00 src

#   File: /project/config
#   Size: 4096       Blocks: 8          IO Block: 4096   directory
# Device: 802h/2050d Inode: 131074      Links: 2
# Access: 2025-02-09 12:00:00.000000000 +0000
# Modify: 2025-02-09 12:00:00.000000000 +0000
# Change: 2025-02-09 12:00:00.000000000 +0000
#  Birth: -

# /project/src:
# -rw-r--r-- 2 user1 developers  0 Feb  9 12:00 main.c
# -rw-r--r-- 2 user1 developers  0 Feb  9 12:00 main_hardlink.c
# lrwxrwxrwx 1 user1 developers 10 Feb  9 12:00 main_symlink -> main.c
# drwxr-xr-x 2 user1 developers  0 Feb  9 12:00 modules
