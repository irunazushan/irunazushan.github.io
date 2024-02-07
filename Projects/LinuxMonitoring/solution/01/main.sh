#!/bin/bash

arg="$1"

if [[ $arg =~ ^[0-9]+$ ]]
then
    echo "Invalid parameter, it must not be a number"
elif [[ $arg =~ ^[[:alpha:]]+$ ]]
then
    echo "Your parameter: $arg" 
else
    echo "Invalid input"
fi
