#!/bin/bash

make -f makefile1
./generate_main.out
make -f makefile2
gcc usersol.c

clear
count=1
cat input.txt | while read line
do
	refsol=`echo $line | ./refsol_main.out`
	if [[ -r refsol.bmp ]]
	then
		refsolbmp=`cat refsol.bmp`
	fi

	usersol=`echo $line | ./a.out`

	if [[ -r usersol.bmp ]]
	then
		userbmp=`cat usersol.bmp`
	fi

	if [[ "$refsol" != "$usersol" ]]
	then
		echo "Fail test N$count"
		echo "Input:"
		echo "$line"
		echo "Your output:"
		echo "$usersol"
		echo "Correct output:"
		echo "$refsol"
		rm -f *.txt *.bmp *.out
		exit 0
	else
		if [[ "$userbmp" != "$refsolbmp" ]]
		then
			echo "Fail test N$count"
			echo "Not correct BMP image"
			rm -f *.txt *.bmp *out
			exit 0
		fi
	fi
	let "count+=1"
done

rm -f *.txt *.out *.bmp
echo "Test End"

