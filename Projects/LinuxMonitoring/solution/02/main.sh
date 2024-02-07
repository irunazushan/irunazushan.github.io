#!/bin/bash

hostname_is="HOSTNAME = $(hostname)"
echo $hostname_is

timezone_is="TIMEZONE = $(timedatectl | awk '/Time zone/{print $3}') UTC $(timedatectl | awk '/Time zone/{print $5}')"
echo $timezone_is

user_is="USER = $(whoami)"
echo $user_is

os_is="OS = $(uname -sr)"
echo $os_is

date_is="DATE = $(date +"%d %B %Y %T")"
echo $date_is

uptime_is="UPTIME = $(uptime)"
echo $uptime_is

uptime_sec_is="UPTIME_SEC = $(awk '{print $1}' /proc/uptime)"
echo $uptime_sec_is

ip_is="IP = $( ifconfig | awk '/inet/ {print $2}' | head -n 1)"
echo $ip_is

mask_is="MASK = $( ifconfig | awk '/inet/ {print $2}' | head -n 1)"
echo $mask_is

gateway_is="GATEWAY = $(ip r | awk '/default/ {print $3}' | head -n 1)"
echo $gateway_is

ram_total_is="RAM_TOTAL = $(free -m | awk '/Mem:/ { printf "%.3f\n", $2/1024 }') GB"
echo $ram_total_is

ram_used_is="RAM_USED = $(free -m | awk '/Mem:/ { printf "%.3f\n", $3/1024 }') GB"
echo $ram_used_is

ram_free_is="RAM_FREE = $(free -m | awk '/Mem:/ { printf "%.3f\n", $4/1024 }') GB"
echo $ram_free_is

space_root_is="SPACE_ROOT = $(df / -hBK | awk '{printf "%.2f\n", $2/1024 }' | tail -1) MB"
echo $space_root_is

space_root_used_is="SPACE_ROOT_USED = $(df / -hBK | awk '{printf "%.2f\n", $3/1024 }' | tail -1) MB"
echo $space_root_used_is

space_root_free_is="SPACE_ROOT_FREE = $(df / -hBK | awk '{printf "%.2f\n", $4/1024 }' | tail -1) MB"
echo $space_root_free_is

# Ask question about saving data to the file

read -p "Do you want to save this data to a file? (y/n): " choice
case "$choice" in 
 [Yy]) 
    # create DD_MM_YY_HH_MM_SS.status filename
    filename=$(date +"%d_%m_%Y_%H_%M_%S").status
    # Save the data to a file
    cat > $filename << EOF
$hostname_is
$timezone_is
$os_is
$date_is
$uptime_is
$uptime_sec_is
$ip_is
$mask_is
$gateway_is
$ram_total_is
$ram_used_is
$ram_free_is
$space_root_is
$space_root_used_is
$space_root_free_is
EOF
    echo "Data saved to $filename"
    ;;
 * ) 
    echo "Data not saved."
    ;;
esac
