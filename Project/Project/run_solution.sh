#!/bin/bash
 #touch commands
 #$nameOfStudentsOutFile="resultOfStudents.csv"
 #echo "$nameOfStudentsOutFile"
 touch changes.diff
 
 ./generate.out     
 #place for student's programm
FILE="./commands"
 while read line ;
do
./checker.out 
 diff r.csv resultOfStudent.csv >changes.diff

 read $main_result<./changes.diff
 if [$main_result == ""]
 then
 echo "Decision is correct"
 else
 echo "Decision is incorrect"
 fi

echo "$line"
done < $FILE
