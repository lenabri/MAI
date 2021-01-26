#!/usr/bin/env zsh

prefix=$1
left=$2
right=$3

if [ $# -eq 1 ]; then
    if [ $prefix = "?" ]; then
        echo "Usage: ./script [prefix] [range from] [range to]"
        echo "The program will delete files with the specified prefix whose length is in the specified range."
    fi
else
    if [ $# -eq 0 ]; then
        echo -n "Enter prefix: "; read prefix
        echo -n "Enter range from: "; read left
        echo -n "Enter range to: "; read right
    elif [ $# -eq 1 ]; then
        echo -n "Enter range from: "; read left
        echo -n "Enter range to: "; read right
    elif [ $# -eq 2 ]; then
        echo -n "Enter range to: "; read right
    fi

    # files=($(ls | grep "$prefix*" | grep -x '.\{'$left','$right'\}'))
    files=($(ls | grep "$prefix*" | egrep '^.{'$left','$right'}$'))
    for i in $files; do
        echo "   " $i removed
        rm $i
    done
fi
