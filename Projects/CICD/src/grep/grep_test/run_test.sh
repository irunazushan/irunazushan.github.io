#!/bin/bash

#random_flags=("-n" "-i" "-c" "-v" "-l" "-h" "-s")
random_flags=("-s")
get_patterns=(
"-f patterns1.txt"
"-f patterns2.txt"
"apple"
"-e 'onion\|inc'"
"-e IPAD")

files=("gtest1.txt" "gtest2.txt" "gtest3.txt" "gtest4.txt")
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
    selected_patterns=""
    num_flags=$((0 + RANDOM % ${#random_flags[@]}))
    num_files=$((1 + RANDOM % ${#files[@]}))
    num_patterns=$((1 + RANDOM % ${#get_patterns[@]}))
    
    for ((i=0; i<num_flags; i++));
    do
        index=$((RANDOM % ${#random_flags[@]}))
        selected_flags+=" ${random_flags[index]}"
    done
    
    for ((j=0; j<num_files; j++));
    do
        index=$((RANDOM % ${#files[@]}))
        selected_files+=" ${files[index]}"
    done
    
    for ((l=0; l<num_patterns; l++));
    do
        index=$((RANDOM % ${#get_patterns[@]}))
        selected_patterns+=" ${get_patterns[index]}"
    done

    ./s21_grep$selected_flags $selected_patterns $selected_files > cmp1
    grep$selected_flags $selected_patterns $selected_files> cmp2
    if diff -q cmp1 cmp2 >/dev/null 2>&1;
    then
        echo "Test $number |grep$selected_flags $selected_patterns $selected_files|: Success"
        ((success++))
    else
        echo "Test $number |grep$selected_flags $selected_patterns $selected_files|: Fail"
        touch differences/diff$((number)).txt
        echo "Test $number |grep$selected_flags $selected_patterns $selected_files|: Fail" >> differences/diff$((number)).txt
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

