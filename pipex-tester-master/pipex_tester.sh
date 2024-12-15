#!/bin/bash

# Colors for output
green="\033[0;32m"
red="\033[0;31m"
yellow="\033[0;33m"
reset="\033[0m"

# Directories and Files
INPUT="assets/deepthought.txt"
OUTPUT_DIR="tests"
PIPEX="..//pipex"
VALGRIND_LOG="${OUTPUT_DIR}/valgrind-log"
BASH_OUTPUT="${OUTPUT_DIR}/bash-output"
PIPEX_OUTPUT="${OUTPUT_DIR}/pipex-output"

# Ensure the output directory exists
mkdir -p $OUTPUT_DIR

# Variables to track test results
passed=0
failed=0

define_result_color() {
    if [ $1 -eq 0 ]; then
        echo -e "${green}[PASS]${reset}"
    else
        echo -e "${red}[FAIL]${reset}"
    fi
}

# Function to run a single test
run_test() {
    local description="$1"
    local bash_cmd="$2"
    local pipex_cmd="$3"
    local test_num="$4"

    echo -e "\n${yellow}Running Test $test_num: $description${reset}"

    # Run the bash command and save output
    eval "$bash_cmd" > "${BASH_OUTPUT}-${test_num}.txt" 2>/dev/null

    # Run the pipex command and save output
    eval "$pipex_cmd" > "${PIPEX_OUTPUT}-${test_num}.txt" 2>/dev/null

    # Compare outputs
    if diff "${BASH_OUTPUT}-${test_num}.txt" "${PIPEX_OUTPUT}-${test_num}.txt" > "${OUTPUT_DIR}/diff-${test_num}.txt"; then
        result=0
        ((passed++))
    else
        result=1
        ((failed++))
    fi
    echo -e "Output Comparison: $(define_result_color $result)"
    if [ $result -ne 0 ]; then
        echo "See diff: ${OUTPUT_DIR}/diff-${test_num}.txt"
    fi

    # Check for memory leaks using Valgrind
    valgrind --leak-check=full --track-origins=yes --log-file="${VALGRIND_LOG}-${test_num}.txt" \
        $PIPEX $INPUT $pipex_cmd > /dev/null 2>&1

    if grep -q "definitely lost: 0 bytes" "${VALGRIND_LOG}-${test_num}.txt"; then
        echo -e "Memory Check: ${green}[PASS]${reset}"
    else
        echo -e "Memory Check: ${red}[FAIL]${reset}"
        echo "See Valgrind log: ${VALGRIND_LOG}-${test_num}.txt"
    fi
}

# Test cases
run_test "cat | hostname" \
    "< $INPUT cat | hostname" \
    "$PIPEX \"$INPUT\" \"cat\" \"hostname\" \"${OUTPUT_DIR}/test-1.txt\"" \
    1

run_test "grep Now | head -2" \
    "< $INPUT grep Now | head -2" \
    "$PIPEX \"$INPUT\" \"grep Now\" \"head -2\" \"${OUTPUT_DIR}/test-2.txt\"" \
    2

run_test "grep Now | wc -w" \
    "< $INPUT grep Now | wc -w" \
    "$PIPEX \"$INPUT\" \"grep Now\" \"wc -w\" \"${OUTPUT_DIR}/test-3.txt\"" \
    3

run_test "grep Now | cat" \
    "< $INPUT grep Now | cat" \
    "$PIPEX \"$INPUT\" \"grep Now\" \"cat\" \"${OUTPUT_DIR}/test-4.txt\"" \
    4

run_test "wc -w | cat" \
    "< $INPUT wc -w | cat" \
    "$PIPEX \"$INPUT\" \"wc -w\" \"cat\" \"${OUTPUT_DIR}/test-5.txt\"" \
    5

run_test "notexisting | wc" \
    "< $INPUT notexisting | wc" \
    "$PIPEX \"$INPUT\" \"notexisting\" \"wc\" \"${OUTPUT_DIR}/test-6.txt\"" \
    6

run_test "cat | notexisting" \
    "< $INPUT cat | notexisting" \
    "$PIPEX \"$INPUT\" \"cat\" \"notexisting\" \"${OUTPUT_DIR}/test-7.txt\"" \
    7

run_test "grep Now | /usr/bin/cat" \
    "< $INPUT grep Now | /usr/bin/cat" \
    "$PIPEX \"$INPUT\" \"grep Now\" \"/usr/bin/cat\" \"${OUTPUT_DIR}/test-8.txt\"" \
    8

run_test "/dev/urandom | head -1" \
    "< /dev/urandom cat | head -1" \
    "$PIPEX \"/dev/urandom\" \"cat\" \"head -1\" \"${OUTPUT_DIR}/test-9.txt\"" \
    9

# Summary
echo -e "\n${yellow}Test Summary:${reset}"
echo -e "${green}Passed:${reset} $passed"
echo -e "${red}Failed:${reset} $failed"
echo "All tests completed. Check the '${OUTPUT_DIR}' directory for results."
echo "Diff files: ${OUTPUT_DIR}/diff-*.txt"
echo "Valgrind logs: ${VALGRIND_LOG}-*.txt"
