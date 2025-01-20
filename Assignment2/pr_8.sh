# 8 char long Alpha-Numeric Password

characters="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

for((i=1; i<=5; i++))
do 
    password=""
    for((j=1; j<=8; j++))
    do
        random=${characters:RANDOM%${#characters}:1}
        password+=$random
    done
    echo "Password $i : $password"
done