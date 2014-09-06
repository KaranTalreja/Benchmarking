#!/bin/bash
# Script to run all the testCases in TestCases directory
reGold=$1
for dir in `cat $reGold`; do
	cp $dir/TEST $dir/GOLD
done;
