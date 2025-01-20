# int main() or void main()

echo -n "Enter the C program file name: "
read filename

if [ ! -f "$filename" ]; then
    echo "File not found!"
    exit 1
fi

if grep -q "void main()" "$filename"; then
    echo "The program uses void main()."
elif grep -q "int main()" "$filename"; then
    echo "The program uses int main()."
else
    echo "The program does not contain main() method or it has a different signature."
fi
