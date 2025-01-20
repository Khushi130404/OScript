# User exist or not

echo -n "Enter Username : "
read user

usernames=($(wmic useraccount get name | awk 'NR>1 {print $1}'))
flag=0

for username in ${usernames[@]};
do
    if [ "$user" == "$username" ]; then
        echo "User Exists"
        flag=1
        break
    fi
done

if [ $flag -eq 0 ]; then
    echo "User does not exist"
fi