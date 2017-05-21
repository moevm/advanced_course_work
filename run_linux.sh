#!/bin/bash

gcc refsol.c -o Sol.out
gcc generate.c -o Gen.out
touch rang

for a in  '1' '2' '3' '4' '5'
do
 ./Gen.out
 ./Sol.out testcase_1 1234 > console_logs
 #echo -en "$a iteretion done" 
done

rm -f testcase_1 Gen.out Sol.out out_trans out_multi rang

exit 0