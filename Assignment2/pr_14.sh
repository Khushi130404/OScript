# Printf() Method

echo -n "Enter the C program file name: "
read file

if [ ! -f "$file" ]; then
    echo "File not found!"
    exit 1
fi

if grep -q "printf(" "$file"; then
    echo "The program contains the printf() method."
else
    echo "The program does not contain the printf() method."
fi
