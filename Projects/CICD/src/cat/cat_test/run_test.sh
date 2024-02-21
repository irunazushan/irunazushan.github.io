#!/bin/bash

#random_flags=("-s" "-v" "-e" "-t" "-b" "-n")
random_flags=("-s")

files=("test1.txt" "test2.txt" "test3.txt" "test4.txt")
fail=0
success=0

number=1

if [ -d "differences" ];
then
    rm -rf differences
    mkdir differences
else
    mkdir differences
fi

echo "GO RANDOM!"
for ((k = 0; k < 100; k++))
do
    selected_flags=""
    selected_files=""
    num_flags=$((0 + RANDOM % 5))
    num_files=$((1 + RANDOM % 4))
    for ((j=0; j<num_files; j++));
    do
        index=$((RANDOM % ${#files[@]}))
        selected_files+=" ${files[index]}"
    done
    
    for ((i=0; i<num_flags; i++));
    do
        index=$((RANDOM % ${#random_flags[@]}))
        selected_flags+=" ${random_flags[index]}"
    done

    ./s21_cat$selected_flags $selected_files > cmp1
    cat$selected_flags $selected_files > cmp2
    if diff -q cmp1 cmp2 >/dev/null 2>&1;
    then
        echo "Test $number |cat$selected_flags $selected_files|: Success"
        ((success++))
    else
        echo "Test $number |cat$selected_flags $selected_files|: Fail"
        touch differences/diff$((number)).txt
        echo "Test $number |cat$selected_flags $selected_files|: Fail" >> differences/diff$((number)).txt
        echo "||$(diff -s cmp1 cmp2)" >> differences/diff$((number)).txt
        ((fail++))
    fi
    ((number++))
done

rm cmp1
rm cmp2

echo "SUCESSs: $success"
echo "FAILs: $fail"
echo "ALL: $((number - 1))"

