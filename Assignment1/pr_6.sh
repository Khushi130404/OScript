# Check Palindrom

echo -n "Enter String : "
read str
rev_str=$(echo "$str" | awk '{for(i=length;i>=1;i--) printf substr($0,i,1);print ""}')
# rev_str=$(echo "$str" | rev)

if [ "$rev_str" == "$str" ]; then 
    echo "Palindrom"
else    
    echo "Not a Palindrom"
fi

# echo -n "Enter String : "
# read str
# rv=""
# len=${#str}
# for(( i=$len-1; i>=0; i-- ))
# do 
#     rv="$rv${str:$i:1}"
# done
# echo "$rv"
