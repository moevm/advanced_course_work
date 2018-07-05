#!/bin/bash

let "max_time = 20"

timeout $max_time ./check_solution.sh
if [ $? -ne 11 ]
then
    echo "RUNTIME ERROR!"
fi

exit 100
