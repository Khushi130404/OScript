sleep 10
bg
echo "In BG"
sleep 10 &
fg %1
echo "In FG"
kill %1
