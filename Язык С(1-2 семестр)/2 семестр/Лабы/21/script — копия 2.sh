#!/usr/bin/env zsh

prefix=$1
left=$2
right=$3
dir=$4

if [ $# -eq 1 ]; then
    if [ $prefix = "?" ]; then
        echo "Usage: ./script [prefix] [range from] [range to] [directory]"
        echo "The program will delete files with the specified prefix whose length is in the specified range."
    fi
else
    if [ $# -eq 0 ]; then
        echo -n "Enter prefix: "; read prefix
        echo -n "Enter range from: "; read left
        echo -n "Enter range to: "; read right
        echo -n "Enter directory: "; read dir
    elif [ $# -eq 1 ]; then
        echo -n "Enter range from: "; read left
        echo -n "Enter range to: "; read right
        echo -n "Enter directory: "; read dir
    elif [ $# -eq 2 ]; then
        echo -n "Enter range to: "; read right
        echo -n "Enter directory: "; read dir
    fi
    
    if [ $# -eq 4 ]; then
        find $dir -maxdepth 1 -name "$prefix*" | egrep '/.{'$left','$right'}$' | xargs rm
    else
        find . -maxdepth 1 -name "$prefix*" | egrep '/.{'$left','$right'}$' | xargs rm
    fi
fi
