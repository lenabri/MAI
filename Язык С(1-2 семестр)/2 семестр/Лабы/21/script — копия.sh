#!/usr/bin/env zsh

# prefix="file"
# left=6
# right=7


echo -n "Enter prefix: "; read prefix
echo -n "Enter range from: "; read left
echo -n "Enter range to: "; read right

files=($(ls | grep "$prefix*" | grep -x '.\{'$left','$right'\}'))

for i in $files; do
    echo "    " $i removed
    rm $i
done
