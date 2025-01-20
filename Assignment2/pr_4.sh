# Greet User based on time

echo "Hello User...!"

hr=$(date +"%H")

if [ "$hr" -lt 12 ]; then
    echo "Good Morning"
elif [ "$hr" -lt 17 ]; then
    echo "Good Afternoon"
elif [ "$hr" -lt 19 ]; then
    echo "Good Evening"
else
    echo "Good Night"
fi