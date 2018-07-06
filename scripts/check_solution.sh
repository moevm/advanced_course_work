#!/bin/bash
echo "Initialization.. "
if [ "$4" == "1337" ] ; then
	setterm -foreground green
	echo "<---d----e----b----u----g--->"
	echo "< Welcome to *debug* mode ! >"
	echo "<---d----e----b----u----g--->"
	sleep 5
	setterm -foreground white
	rm -rf bmp_files
	mkdir bmp_files
fi
make -s
if [ $? -ne 0 ] ; then
	setterm -foreground red
	echo "Wrong compilation."
	setterm -foreground white
	exit 100
fi
if [ ! -z "$5" ] ; then
	echo "Wrong generation arguments, parameters choosed by default"
fi
./gen_bmp $1 $2 $3
file="commands.txt"
counter=0;
while read line
do
let counter=$counter+1
if [ "$4" == "1337" ] ; then
	echo -e "\n---------------------------------------------------------------\n"
	echo "> Test №$counter"
	echo "> Commands to input of reference: $line"
fi
tmp=$( ./my_solution <<< $line )
buf=$( ./edit_bmp <<< $line )
if [ "$4" == "1337" ] ; then
	if [ "$buf" != "" ] ; then
		echo "> True reference tell: $buf"
	else
		echo "> True reference tell nothing."
	fi
	if [ "$tmp" != "" ] ; then
		echo "> Another reference tell: $tmp"
	else
		echo "> Another reference tell nothing."
	fi
fi
if [ "$tmp" != "$buf" ] ; then
	echo "---------------------------"
	setterm -foreground red
  echo "Failed with test №$counter"
	if [ -z $4 ] ; then
	echo "> Commands to input of reference: $line"
		if [ "$buf" != "" ] ; then
			echo "> True reference tell: $buf"
		else
			echo "> True reference tell nothing."
		fi
		if [ "$tmp" != "" ] ; then
			echo "> Another reference tell: $tmp"
		else
			echo "> Another reference tell nothing."
		fi
	fi
	setterm -foreground white
	echo "---------------------------"
	if [ "$4" == "1337" ] ; then
		echo -e "\n> Fail with test №$counter <\n$line\nExpected output: "$buf" \n Your output: "$tmp"" >> bmp_files/list_failed_tests.txt
		continue
	fi
	exit 100
elif [ "$tmp" == "$buf" ] && [ "$buf" != "" ] ; then
	if [ "$4" == "1337" ] ; then
		setterm -foreground green
		echo "> Correct reaction to wrong commands."
		setterm -foreground white
	fi
	continue
else
	if [ "$4" == "1337" ] ; then
		setterm -foreground green
		echo "> Txt output are equal."
		setterm -foreground white
		echo "> Comparing .bmp files..."
	fi
fi
tmp=$( ./compare_bmp /dev/null 2>&1 )
if [ $? -ne 0 ] ; then
	echo "---------------------------"
	setterm -foreground red
	echo "Failed with test №$counter"
	echo "> Commands to input of reference: $line"
	echo "> $tmp"
        setterm -foreground white
	echo "---------------------------"
	if [ "$4" == "1337" ] ; then
		echo -e "\n> Fail with test №$counter <\n$line\nBMP files are not equal.\n" >> bmp_files/list_failed_tests.txt
		mv output_file.bmp bmp_files/True_T№$counter.bmp
		mv my_solution.bmp bmp_files/Custom_T№$counter.bmp
		continue
	fi
	exit 100
fi
if [ "$4" == "1337" ] ; then
	setterm -foreground green
	echo "> $tmp"
	setterm -foreground white
	mv output_file.bmp bmp_files/True_T№$counter.bmp
	mv my_solution.bmp bmp_files/Custom_T№$counter.bmp
else
	rm -f "output_file.bmp"
	rm -f "my_solution.bmp"
fi
done < $file
echo -e "\n---------------------------------------------------------------\n"
setterm -foreground green
echo "All test complete succesful! Good job!"
if [ "$4" == "1337" ] ; then
	echo "(But maybe that becouse you in *debug* mode)"
fi
setterm -foreground white
echo -e "\n---------------------------------------------------------------"
exit 100
