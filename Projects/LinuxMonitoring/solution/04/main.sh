#!/bin/bash

source color_config.txt

declare bg_colors=( ["1"]="47" ["2"]="41" ["3"]="42" ["4"]="44" ["5"]="45" ["6"]="40" )
declare fg_colors=( ["1"]="37" ["2"]="31" ["3"]="32" ["4"]="34" ["5"]="35" ["6"]="30" )

declare bg_color_names=( ["1"]="white" ["2"]="red" ["3"]="green" ["4"]="blue" ["5"]="purple" ["6"]="black" )
declare fg_color_names=( ["1"]="white" ["2"]="red" ["3"]="green" ["4"]="blue" ["5"]="purple" ["6"]="black" )

#column1_background
if [[ ${column1_background} =~ ^[1-6]$ ]]
then
bg1=${bg_colors[${column1_background}]}
echo "Column 1 background = ${column1_background} (${bg_color_names[${column1_background}]})"
else
bg1=${bg_colors[2]}
echo "Column 1 background = default (${bg_color_names[2]})"
fi

#column1_font_color
if [[ ${column1_font_color} =~ ^[1-6]$ ]]
then
fg1=${fg_colors[${column1_font_color}]}
echo "Column 1 font color = ${column1_font_color} (${fg_color_names[${column2_font_color}]})"
else
fg1=${fg_colors[1]}
echo "Column 1 font color = default (${fg_color_names[1]})"
fi

#column2_background
if [[ ${column2_background} =~ ^[1-6]$ ]]
then
bg2=${bg_colors[${column2_background}]}
echo "Column 2 background = ${column2_background} (${bg_color_names[${column2_background}]})"
else
bg2=${bg_colors[3]}
echo "Column 2 background = default (${bg_color_names[3]})"
fi

#column2_font_color
if [[ ${column2_font_color} =~ ^[1-6]$ ]]
then
fg2=${fg_colors[${column2_font_color}]}
echo "Column 2 font color = ${column2_font_color} (${fg_color_names[${column2_font_color}]})"
else
fg2=${fg_colors[6]}
echo "Column 2 font color = default (${fg_color_names[6]})"
fi

if [ $(($bg1 - 10)) = $fg1 ] || [ $(($bg2 - 10)) = $fg2 ]
    then
    echo "Error: Font and background colors of one column must not match."
    echo "Please call the script again with different parameters."
    exit 1
fi

hostname_is="HOSTNAME = $(hostname)"
user_is="USER = $(whoami)"


vars=(
"HOSTNAME = $(hostname)"
"TIMEZONE = $(timedatectl | awk '/Time zone/{print $3}') UTC $(timedatectl | awk '/Time zone/{print $5}')"
"USER = $(whoami)"
"OS = $(uname -sr)"
"DATE = $(date +"%d %B %Y %T")"
"UPTIME = $(uptime)"
"UPTIME_SEC = $(awk '{print $1}' /proc/uptime)"
"IP = $( ifconfig | awk '/inet/ {print $2}' | head -n 1)"
"MASK = $( ifconfig | awk '/inet/ {print $2}' | head -n 1)"
"GATEWAY = $(ip r | awk '/default/ {print $3}' | head -n 1)"
"RAM_TOTAL = $(free -m | awk '/Mem:/ { printf "%.3f\n", $2/1024 }') GB"
"RAM_USED = $(free -m | awk '/Mem:/ { printf "%.3f\n", $3/1024 }') GB"
"RAM_FREE = $(free -m | awk '/Mem:/ { printf "%.3f\n", $4/1024 }') GB"
"SPACE_ROOT = $(df / -hBK | awk '{printf "%.2f\n", $2/1024 }' | tail -1) MB"
"SPACE_ROOT_USED = $(df / -hBK | awk '{printf "%.2f\n", $3/1024 }' | tail -1) MB"
"SPACE_ROOT_FREE = $(df / -hBK | awk '{printf "%.2f\n", $4/1024 }' | tail -1) MB"
)

for var in "${vars[@]}"; do
    # Split the variable into words
    IFS=' ' read -ra words <<< "$var"

    first_word="${words[0]}"
    rest_of_words="${words[@]:2}"
     printf "\033[${bg1};${fg1}m${first_word}\033[0m = \033[${bg2};${fg2}m${rest_of_words}\033[0m\n"
done
