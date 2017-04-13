#!/bin/bash

#gcc -o generate generate.c
#./generate

gcc -o refsol refsol.c
gcc -o usersol usersol.c

refoutTXT=refout.txt
useroutTXT=userout.txt
refoutBMP=REFOUT.bmp
useroutBMP=USEROUT.bmp

i=1
while [ $i -ne 50 ]
do
    read test
    echo $test > test.txt
    ./refsol < test.txt > refout.txt 2>&1
    ./usersol < test.txt > userout.txt 2>&1
    cmp -s $refoutTXT $useroutTXT
    if [ $? -ne 0 ]
    then
        echo "Failed test №$i."
        echo "Correct output:"
        cat refout.txt
        echo
        echo "Your output:"
        cat userout.txt
        echo
        exit 0
    fi
    read output < refout.txt
    if [ "$output" == "Look OUT.bmp" ]
    then
        cmp -s $refoutBMP $useroutBMP
        if [ $? -ne 0 ]
        then
            echo "Failed test №$i."
            echo "Wrong USEROUT.bmp"
            exit 0
        fi

    fi
    let "i += 1"
done < generatedData.txt
echo "Good job!"
