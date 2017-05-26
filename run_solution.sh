#!/bin/bash

delete_all() 
{
rm -f testcase Gen.exe Sol.exe uSol.exe commands
rm -f ref_trans ref_multi
rm -f trans multi
rm -f console_logs user_console_logs   
}

check_console()
{
if ! cmp -s console_logs user_console_logs
    then
        echo "Failed with test #$current_test"
        echo "Console logs are wrong."
        echo 
        echo "Correct output:"
        cat console_logs
        echo 
        echo "Your output:"
        cat user_console_logs
        delete_all
        exit 100
fi 
}

check_trans()
{
if [ -f "ref_trans" ]
then
    if [ -f "trans" ]
    then
        if ! cmp -s multi ref_multi 
        then
            echo "Failed with test #$current_test"
            echo "Transpose is wrong."
            echo
            echo "Correct output:"
            cat ref_trans
            echo
            echo "Your output:"
            cat trans
            delete_all
            exit 100
        fi 
    else
        echo "Failed with test #$current_test"
        echo "Transpose is wrong:"
        echo "No file."
        delete_all
        exit 100
    fi
else 
    if [ -f "trans" ]
    then
        echo "Failed with test #$current_test"
        echo "Transpose is wrong:"
        echo "File exists but not."
        delete_all
        exit 100
    fi
fi 
}

check_multi()
{
if [ -f "ref_multi" ]
then
    if [ -f "multi" ]
    then
        if ! cmp -s multi ref_multi 
        then
            echo "Failed with test #$current_test"
            echo "Multiplication is wrong."
            echo
            echo "Correct output:"
            cat ref_multi
            echo
            echo "Your output:"
            cat multi
            delete_all
            exit 100
        fi 
    else
        echo "Failed with test #$current_test"
        echo "Multiplication is wrong:"
        echo "No file."
        delete_all
        exit 100
    fi
else 
    if [ -f "multi" ]
    then
        echo "Failed with test #$current_test"
        echo "Multiplication is wrong:"
        echo "File exists but not."
        delete_all
        exit 100
    fi
fi 
}

test_no_file()
{
./Sol.exe no_file 1234 > console_logs
./uSol no_file 1234 > user_console_logs
check_console
check_trans
check_multi
rm -f console_logs user_console_logs 
let "current_test+=1"
}

test_empty_file()
{
touch empty
./Sol.exe empty 1234 > console_logs
./uSol.exe empty 1234 > user_console_logs
rm -f empty
check_console
check_trans
check_multi
rm -f console_logs user_console_logs 
let "current_test+=1"
}

test_arg()
{
number_of_tests=10
current_line=1
let "number_of_tests+=1"
./GetCommand.exe "$1" "$number_of_tests" > commands
while [ $current_line -lt $number_of_tests ]
do
    arg=$( sed -n "$current_line"p commands )
echo "$1 arguments in test $current_test !"
echo "Arg is $arg"
    ./Gen.exe
    ./Sol.exe testcase "$arg" > console_logs
    ./uSol.exe testcase "$arg" > user_console_logs
    check_console
    check_trans
    check_multi
    rm -f console_logs user_console_logs
    rm -f ref_multi ref_trans
    rm -f multi trans 
    let "current_test+=1"
    let "current_line+=1"
done
    rm -f commands
}

test_random_arguments(){
cur_arg_numb=1
max_arg_numb=4
let "max_arg_numb+=1"
while [ $cur_arg_numb -lt $max_arg_numb ]
do
    test_arg "$cur_arg_numb"
    echo
    echo
    let "cur_arg_numb+=1"
done
}

current_test=1

gcc gencommands.c -o GetCommand.exe
gcc refsol.c -o Sol.exe
gcc generate.c -o Gen.exe
gcc usersol_inc_trans.c -o uSol.exe

test_random_arguments
echo "test no file test number $current_test"
test_no_file
echo "test empty file test number $current_test"
test_empty_file

REPEATS=5
let "REPEATS+=current_test"
while [ $current_test -lt $REPEATS ]
do
    echo "testing... test number is $current_test ." 
 ./Gen.exe
 ./Sol.exe testcase 1234 > console_logs
 ./uSol.exe testcase 1234 > user_console_logs

check_console
check_multi
check_trans

rm -f testcase ref_trans ref_multi console_logs user_console_logs

let "current_test+=1"
done

delete_all


exit 0