#!/bin/bash

let TIME=10

if [ ! -z "$1" ] ; then
	TIME=$1
fi

if [ "$5" == "1337" ] ; then
	let TIME=$TIME+1
fi

timeout $TIME ./check_solution.sh $2 $3 $4 $5

if [ $? -ne 100 ] ; then
	setterm -foreground red
	echo -e "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	echo "> Runtime error! (execution time more then $1 sec.)"
	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	setterm -foreground white
fi

rm -f "output_file.bmp"
rm -f "my_solution.bmp"
rm -f "input_file.bmp"
rm -f "commands.txt"
rm -f "my_solution"
rm -f "gen_bmp"
rm -f "edit_bmp"
rm -f "compare_bmp"
