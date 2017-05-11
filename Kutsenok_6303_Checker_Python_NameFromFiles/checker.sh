#!/bin/bash
random_word="$(python -c 'import main; print main.generate()')"
echo $random_word
output=$(python -c "import main; print main.solve(\"$random_word\")")
output=$(echo $random_word | ./untitled)
result_string="${output//$'\n'/ }"
echo $result_string
result=$(python -c "import main; print main.check(\"$result_string\",\"$random_word\")")
echo $result