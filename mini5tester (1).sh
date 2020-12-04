#!/bin/bash
check_for_source()
{
    if [[ ! -f "$1" ]]
    then
        echo "Source file '$1' not found. Please make sure to upload the mini tester script into the same folder as your source files."
        exit 1;
    fi
}

print_and_run()
{
    echo "\$ $1"
    bash -c "$1"
    echo -e "exit code: $?"
}

check_for_source "report.c"
check_for_source "data.csv"

# BEGIN SETUP
sourcedir=$PWD
tmpdir=/tmp/__tmp_comp206_${LOGNAME}
mkdir -p "$tmpdir"
cp report.c data.csv "$tmpdir"
cd "$tmpdir"


echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  report.c tests @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo
echo "[[[[ test case 0: compiling report.c ]]]]"
echo
echo "********************************************************************************"
print_and_run "gcc -o report report.c"
echo "********************************************************************************"
echo
echo "[[[[ test case 1: EXPECTED TO FAIL - missing parameter ]]]]"
echo
echo "********************************************************************************"
print_and_run "./report data.csv"
echo "********************************************************************************"
echo
echo "[[[[ test case 2: EXPECTED TO FAIL - data file can't be read ]]]]"
echo "********************************************************************************"
echo
print_and_run "./report nosuchdata.csv 'Jane Doe' rpt.txt"
echo '********************************************************************************'
echo
echo "[[[[ test case 3: EXPECTED TO FAIL - user not in data file ]]]]"
echo "********************************************************************************"
echo
print_and_run "./report data.csv 'Jane Doe' rpt.txt"
echo '********************************************************************************'
echo
echo "[[[[ test case 4: EXPECTED TO WORK - no collaborators found ]]]]"
echo '********************************************************************************'
echo
print_and_run "./report data.csv 'Markus Bender' rpt.txt"
cat rpt.txt
chmod -w rpt.txt
echo
echo "[[[[ test case 5: EXPECTED TO FAIL - output file can't be opened ]]]]"
echo '********************************************************************************'
echo
print_and_run "./report data.csv 'Markus Bender' rpt.txt"
chmod +w rpt.txt
echo '********************************************************************************'
echo
echo "[[[[ test case 6: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv 'Adaline Murphy' rpt.txt"
cat rpt.txt
echo

#CLEAN UP
rm -r "$tmpdir"
