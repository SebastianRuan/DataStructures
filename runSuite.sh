#!/bin/bash
suite_file="$1"
program="$2"
path=$(dirname $suite_file)/
echo $path/
allPassed=1
count=0

#test for correct number of arguments passed to script
if [ $# -ne 2 ]; then
	>&2 echo "incorrect number of arguments passed"
	exit 1
fi

true > memory_leaks.txt
#for every testfile in suite_file find the associated .in file and run program with .in file contents as input
for testfile in $(cat $suite_file); do
  ((count=count+1))
	if [[ -r "$path$testfile.in" && -f "$path$testfile.in" ]]; then #test for file existance
		
		if [[ -r "$path$testfile.out" && -f "$path$testfile.out" ]]; then
			if [[ -r "$path$testfile.args" && -f "$path$testfile.args" ]]; then #if program takes in own arguments find associated .arg files
				arguments=""
				for onearegument in $(cat "$testfile.args"); do
					arguments+=" $onearegument"
				done
			fi

			actualOutput=$(mktemp)
			valgrind --leak-check=yes "$program$arguments" < "$path$testfile.in" > "$actualOutput" 2>> memory_leaks.txt #execute program with testing input and put computed value into temp file ($actualOutput)
			diff "$actualOutput" "$path$testfile.out" > /dev/null #compare files
			
			if [ $? -ne 0 ]; then #if diff does not return 0 then there is a difference between actual output and .out file
				allPassed=0
				echo "Test failed: $path$testfile"
				echo "Input:"
				cat "$path$testfile.in"
				echo "Expected:"
				cat "$path$testfile.out"
				echo "Actual:"
				cat $actualOutput
			else
			  echo "$testfile passed"
			fi

		  rm "$actualOutput"
			#if above tests failed then error .in or .out files are missing
		else
			>&2 echo "file $path$testfile.out is missing or unreadable"
			exit 3
		fi
	else 
		>&2 echo "file $path$testfile.in is missing or unreadable"
		exit 2
	fi
done

if [ "$(grep -o 'no leaks are possible' memory_leaks.txt | wc -l)" -ne $count ]; then
  echo "MEMORY LEAK"
elif [ $allPassed -eq 1 ]; then
  echo "ALL TESTS PASSED"
fi
