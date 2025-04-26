# Simple Calculator

echo "Enter 1st Number"
read n1
echo "Enter 2nd Number"
read n2
echo "Enter Operator"
read op

if [ "$op" = "+" ]; then
    echo "Ans : $((n1+n2))"
elif [ "$op" = "-" ]; then
    echo "Ans : $((n1-n2))"
elif [ "$op" = "*" ]; then
    echo "Ans : $((n1*n2))"
elif [ "$op" = "/" ]; then
    if [ "$n2" -eq 0 ]; then
        echo "Division By Zero"
    else
        echo "Ans : $((n1/n2))"
    fi
else
    echo "Invalid Operator"
fi


# echo -n "Enter Number 1 : "
# read n1
# echo -n "Enter Number 2 : "
# read n2
# echo -n "Enter op : "
# read op
# case $op in
#     "+") echo "Add : $((n1+n2))";;
#     "-") echo "Sub : $((n1-n2))";;
#     "*") echo "Mult : $((n1*n2))";;
#     "/") echo "Div : $((n1/n2))";;
#     *) echo "Invalid";;
# esac