# Reverse Number

echo -n "Enter Number : "
read n

rev=0

while [ $n -ne 0 ]
do
    rev=$((rev*10+n%10))
    n=$((n/10))
done

echo "Reverse : $rev"