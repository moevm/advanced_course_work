#!/bin/bash

rm_fun()
{
if [ -e refsol ] 
then
rm refsol
fi
if [ -e usersol ] 
then
rm usersol
fi
if [ -e generate ] 
then
rm generate
fi
if [ -e MasterOut.txt ] 
then
rm MasterOut.txt
fi
if [ -e UserOut.txt ]  
then
rm UserOut.txt
fi
if [ -e MasterAfterSort.txt ] 
then
rm MasterAfterSort.txt
fi
if [ -e UserAfterSort.txt ] 
then
rm UserAfterSort.txt
fi
if [ -e usererr.txt ]
then
rm usererr.txt
fi
}
 gcc -o refsol refsol.c

# генерация тестов
if [ ! -e test1.txt ]
then 
	gcc -o generate generate.c
	./generate > fileinfo.txt
fi
 gcc -o usersol usersol.c 1> usererr.txt 2>&1
code_return=$?
usererr=usererr.txt
if [ $code_return -ne 0 ]
	then
	echo "Error:"
	cat usererr.txt
	rm_fun
	exit 0
fi
i=1
file="fileinfo.txt"
input=input
while read line
do
cat "$line" > testcheck.txt
echo -e "\n" >> testcheck.txt
cat "$input">>testcheck.txt
test=testcheck.txt
# запуск программ с тестами
./refsol 0< $test 1> MasterOut.txt 2>&1 
master_code=$?
MasterSort=MasterAfterSort.txt
MasterOut=MasterOut.txt
./usersol 0< $test 1> UserOut.txt 2>&1
user_code=$?
UserOut=UserOut.txt
UserSort=UserAfterSort.txt
if [ $master_code -ne $user_code ]
	then
	echo "Failed with test№$i"
	echo "Wrong return value"
	rm_fun
	exit 0
fi
# сравнение сортированных матриц
if [ "$master_code" -eq 0 ] && [ "$user_code" -eq 0 ]
then
	cmp -s $MasterSort $UserSort
	 if [ $? -ne 0 ]
	 then
	echo "Failed with test№$i"
	echo "input:"
	cat $test
	echo "Your output"
	cat $UserSort
	echo "Correct output"
	cat $MasterSort
	rm_fun
	 exit 0
	fi
else		
	cmp -s $MasterOut $UserOut
	if [ $? -ne 0 ]
		then
		echo "Failed with test№$i"	
		echo "input:"
		cat $test
		echo "Your output"
		cat $UserOut
		echo "Correct output"
		cat $MasterOut
		rm_fun
		exit 0
	fi
fi
let "i+=1"
done < "$file" 
echo "Good Job"
rm_fun
exit 0
