#!/bin/bash
# 1. Линковка и запуск тестовых данных
# 2. Линковка и запуск эталонного решения с данным набором тестовых данных
# 3. запуск пользовательского решения с данным набором тестовых данных
# 4. Сравнение результатов и вывод ответа, верное ли решение

cd generator
make
./generate

cd ..
cd refsol
make
./refsol

cd ..
gcc -o usersol usersol.c 2>&1
exit_code=$?
if [ $exit_code -ne 0 ]
then
    echo "Compilation error:"
    cat userout.txt
    if [ -e userout.txt ]
    then
        rm userout.txt
    fi
    if [ -e usersol ]
    then
        rm usersol
    fi
    exit 0
fi

i=1

while [ $i -le 20 ]
do
let "j=1+5*i-5"
k=1
while read line; do
	./usersol 0< test/input_file_$i.txt $line 1> userout.txt 2>&1 
    exit_code=$?
    if [ $exit_code -ne 0 ]
    then
        echo "Failed test №$j."
        echo "Test input:"
        echo "$line";
        cat test/input_file_$i.txt
        
        if [ -e userout.txt ]
		then
        	rm userout.txt
    	fi
    	if [ -e usersol ]
    	then
        	rm usersol
    	fi
        exit 0	
	else
	 cmp -s userout.txt result/output_file_${i}x${k}.txt
        if [ $? -ne 0 ]
        then
            echo "Failed test №$j."
            echo
            if [ -e userout.txt ]
			then
				rm userout.txt
			fi
			if [ -e usersol ]
			then
				rm usersol
			fi
            exit 0
        fi
	fi
	let "j+=1"
	let "k+=1"
done < ./test/commands_$i.txt
  let "i+=1"  
done

 if [ -e userout.txt ]
			then
				rm userout.txt
			fi
			if [ -e usersol ]
			then
				rm usersol
			fi
echo "Good job!"
