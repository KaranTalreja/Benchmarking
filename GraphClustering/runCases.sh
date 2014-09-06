#!/bin/bash
# Script to run all the testCases in TestCases directory
mkdir -p TestResult
failed=TestResult/failedCases
rm -f $failed
touch $failed
for dir in ./TestCases/*; do
touch $dir/TEST
cat $dir/TestCase | ./bin/exec > $dir/TEST
if [ -f $dir/GOLD ]; then
NEW=`diff $dir/GOLD $dir/TEST`
if [ -z "$NEW" ]; then
    echo "PASSED $dir"
else
    echo "FAILED $dir"
    echo "$dir" >> $failed
fi
else
    echo "INCOMPLETE $dir"
fi
done;
