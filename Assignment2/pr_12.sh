# Current Logged in time

logged_in_user=$(whoami)
login_time=$(cmd.exe /c "query user $logged_in_user" | sed -n '2p' | awk '{print $3, $4}')

echo "You logged in at: $login_time"