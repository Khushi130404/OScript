sleep 10
bg
echo "In BG"
sleep 10 &
fg %1
echo "In FG"
kill %1

# Khushi@KhushiLaptop MINGW64 /d/OScript/Assignment3/Process_Management (Submission)
# $ bash pr_2.sh
# In BG
# [1] 1234
# In FG
# [1]+  Terminated   sleep 10
