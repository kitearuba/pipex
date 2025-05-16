#!/bin/bash

# Path to the compiled pipex_bonus binary
BIN="../pipex_bonus"
RESET="\033[0m"
GREEN="\033[1;32m"
RED="\033[1;31m"

# Helper to compare results
function check_output() {
	diff "$1" "$2" > /dev/null 2>&1
	if [ $? -eq 0 ]; then
		echo -e "$GREEN[OK]$RESET $3"
	else
		echo -e "$RED[FAIL]$RESET $3"
		diff "$1" "$2"
	fi
}

# Create clean working dir
mkdir -p tmp
cd tmp || exit

# === Test 1: Two commands ===
echo "hello world" > infile.txt
$BIN infile.txt "tr a-z A-Z" "rev" outfile1.txt
echo "hello world" | tr a-z A-Z | rev > expected1.txt
check_output outfile1.txt expected1.txt "Test 1: tr + rev"

# === Test 2: Three commands ===
echo "apple banana" > infile.txt
$BIN infile.txt "tr a-z A-Z" "rev" "wc -c" outfile2.txt
echo "apple banana" | tr a-z A-Z | rev | wc -c > expected2.txt
check_output outfile2.txt expected2.txt "Test 2: tr + rev + wc"

# === Test 3: ls + grep + wc ===
touch file1.txt file2.txt my_file.txt
$BIN infile.txt "ls" "grep file" "wc -l" outfile3.txt
ls | grep file | wc -l > expected3.txt
check_output outfile3.txt expected3.txt "Test 3: ls + grep + wc"

# === Test 4: here_doc mode ===
$BIN here_doc END "cat -e" "wc -l" heredoc_out.txt << EOF
line one
line two
END

echo "line one$" > tmp_input.txt
echo "line two$" >> tmp_input.txt
wc -l < tmp_input.txt > expected4.txt
check_output heredoc_out.txt expected4.txt "Test 4: here_doc with cat -e + wc"

# Cleanup temporary files
cd ..
rm -rf tmp
