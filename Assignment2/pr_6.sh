# Length of each String using Array

echo -n "Enter a Sentence : "
read str
words=($str)

for word in "${words[@]}";
do
    echo "$word : ${#word}"
done