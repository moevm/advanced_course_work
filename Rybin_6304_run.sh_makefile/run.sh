#!/bin/bash

make
./Generator

count=0
cat commands.txt|while read line
do
	
	refsol_stdout=`./Refsol $line` 	
	if [[ -r results.csv ]]
	then
			refsol_fileout=`cat results.csv`	
	fi

	usersol_stdout=`./Usersol $line`
	if [[ -r results.csv ]]
	then
			usersol_fileout=`cat results.csv`
	fi
	
	if [[ "$refsol_stdout" !=  "$usersol_stdout" ||
		-n "$refsol_fileout" && -n "$usersol_fileout" && "$refsol_fileout" != "$usersol_fileout" ]]
	then
		echo "Fail test $count"
		echo "Correct out put: $refsol_stdout"
		echo "Your output: $usersol_stdout"
		rm Generator Refsol Usersol input_file_1.csv input_file_2.csv commands.txt
		if [[ -e results.csv ]]			
		then
			rm results.csv
		fi
		exit 1
	fi
	
	count=$(( $count + 1 ))
done 

rm Generator Refsol Usersol input_file_1.csv input_file_2.csv commands.txt  
if [[ -e results.csv ]]
then
	rm results.csv
fi

echo "Test succsesful"
exit 0


