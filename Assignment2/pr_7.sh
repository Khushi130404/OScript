# Display Longest & Shortest Username

usernames=($(wmic useraccount get name | awk 'NR>1 {print $1}'))
long=${usernames[0]}
short=${usernames[0]}

for user in ${usernames[@]};
do
    if [ ${#user} -gt ${#long} ]; then
        long=$user
    fi
    if [ ${#user} -lt ${#short} ]; then
        short=$user
    fi
done

echo "Longest : $long"
echo "Shortest : $short"