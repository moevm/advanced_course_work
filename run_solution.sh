#!/bin/bash

for a in  '1' '2' '3' '4' '5'
do
 ./Gen
 ./Sol testcase_1 1234 > rang
done

rm -f testcase_1 Gen.exe Sol.exe out_trans out_multi rang

exit 0