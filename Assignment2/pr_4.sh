# Greet User based on time

echo "Hello User...!"
time=$(date +"%H")

if [ $time -lt 4 ]; then 
    echo "Good Night"
elif [ $time -lt 12 ]; then
    echo "Good Morning"
elif [ $time -lt 17 ]; then
    echo "Good Afternoon"
elif [ $time -lt 20 ]; then
    echo "Good Evening"
else
    echo "Good Night"
fi