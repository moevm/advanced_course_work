#!/bin/bash

# Данный скрипт выполняет следующие функции:
# 1. запуск генерации тестовых данных
# 2. запуск эталонного решения с данным набором тестовых данных
# 3. запуск пользовательского решения с данным набором тестовых данных
# 4. сравнение результатов и вывод ответа, верное ли решение
# 5. удаление всех временных txt и bmp файлов

# Скрипт следует запускать следующей командой: ./run_solution.sh 2> userout.txt

# By Foksen 13.04.17 (Last update 17.04.17)

# функция удаляет все существующие временные файлы
rm_files ()
{
    if [ -e refout.txt ]
    then
        rm refout.txt
    fi
    if [ -e userout.txt ]
    then
        rm userout.txt
    fi
    if [ -e REFOUT.bmp ]
    then
        rm REFOUT.bmp
    fi
    if [ -e USEROUT.bmp ]
    then
        rm USEROUT.bmp
    fi
    if [ -e test.txt ]
    then
        rm test.txt
    fi
    if [ -e usersol ]
    then
        rm usersol
    fi
}

refoutTXT=refout.txt
useroutTXT=userout.txt
refoutBMP=REFOUT.bmp
useroutBMP=USEROUT.bmp

gcc -o usersol usersol.c 1> userout.txt 2>&1
exit_code=$?
if [ $exit_code -ne 0 ]
then
    echo "Compilation error:"
    cat userout.txt
    rm_files
    exit 0
fi

i=1
while [ $i -le 50 ]
do
    read test
    echo $test 1> test.txt
    ./refsol 0< test.txt 1> refout.txt 2>&1
    ./usersol 0< test.txt 1> userout.txt 2>&1
    exit_code=$?
    if [ $exit_code -ne 0 ]
    then
        echo "Failed test №$i."
        echo "Test input:"
        cat test.txt
        cat userout.txt
        rm_files
        exit 0
    else
        cmp -s $refoutTXT $useroutTXT
        if [ $? -ne 0 ]
        then
            echo "Failed test №$i."
            echo "Test input:"
            cat test.txt
            echo "Correct output:"
            cat refout.txt
            echo
            echo "Your output:"
            cat userout.txt
            echo
            rm_files
            exit 0
        fi
        read output 0< refout.txt
        if [ "$output" == "Look OUT.bmp." ]
        then
            cmp -s $refoutBMP $useroutBMP
            if [ $? -ne 0 ]
            then
                echo "Failed test №$i."
                echo "Test input:"
                cat test.txt
                echo "Wrong USEROUT.bmp"
                rm_files
                exit 0
            fi

        fi
    fi
    let "i += 1"
done 0< generatedData.txt
rm_files
echo "Good job!"
