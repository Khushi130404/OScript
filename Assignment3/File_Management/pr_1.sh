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

