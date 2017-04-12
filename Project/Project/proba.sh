#!/bin/bash
commands="$(commands)"

while read -r line;
do 
echo "$line";
done < <(commands)
