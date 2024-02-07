#!/bin/bash

# Start of the execution time
SECONDS=0

total_folders=$(find "$1" -type d | wc -l)
echo "Total number of folders (including all nested ones) = $total_folders"

top_folders=$(du -sh "$1"/* | sort -rh | head -5 | awk '{ printf "%d - %s, %s\n", NR, $2, $1 }')
echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
echo "$top_folders"

total_files=$(find "$1" -type f | wc -l)
echo "Total number of files = $total_files"

#Number of configuration files, text files, executable files, log files, archives, symbolic links
num_conf_files=$(find "$1" -type f -name "*.conf" | wc -l)
num_text_files=$(find "$1" -type f -name "*.txt" | wc -l)
num_exec_files=$(find "$1" -type f -perm /u=x,g=x,o=x | wc -l)
num_log_files=$(find "$1" -type f -name "*.log" | wc -l)
num_archives=$(find "$1" -type f -name "*.tar.gz" | wc -l)
num_symbolic_links=$(find "$1" -type l | wc -l)
echo "Number of:"
echo "Configuration files (with the .conf extension) = $num_conf_files"
echo "Text files = $num_text_files"
echo "Executable files = $num_exec_files"
echo "Log files (with the extension .log) = $num_log_files"
echo "Archive files = $num_archives"
echo "Symbolic links = $num_symbolic_links"


# Top 10 files with largest size in descending order (path, size and type)
top_files=$(find "$1" -type f -exec du -sh {} \; | sort -hr | head -10 | awk -F'[[:space:]]+' '{print NR " -", $2, ",", $1, ",", substr($2, index($2, ".")+1)}')
echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
echo "$top_files"

# Top 10 executable files with largest size in descending order (path, size and hash)
echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
top_files=$(find "$1" -type f -exec du -sh {} \; | sort -hr | head -10)
counter=1
while IFS= read -r line; do
    file=$(echo $line | awk '{print $2}')
    size=$(echo $line | awk '{print $1}')
    md5=$(md5sum "$file" | awk '{print $1}')

    echo "${counter} - ${file}, ${size}, ${md5}"
    ((counter++))
done <<< "$top_files"

execution_time=$SECONDS
echo "Script execution time (in seconds) = $execution_time"
