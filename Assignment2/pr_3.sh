# Fibonacci

echo -n "Enter Number : "
read n

a=0
b=1
c=$((a+b))

for((i=0; i<n; i++))
do
    echo "$a"
    a=$((b))
    b=$((c))
    c=$((a+b))
done
