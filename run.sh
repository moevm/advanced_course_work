#!/bin/bash

gcc sol.c -o Sol
gcc gen.c -o Gen

for a in  '1' '2' '3' '4' '5'
do
 ./Gen
 ./Sol testcase_1 1234
 #echo -en "$a iteretion done" 
done

rm testcase_1
rm Gen.exe
rm Sol.exe
rm out_trans
rm out_multi


#if cmp -s example example1
#   then echo Same!
#fi

exit 0