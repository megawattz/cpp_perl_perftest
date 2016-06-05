#!/bin/bash

if [ $# -lt 2 ]; then
    echo 'usage ./test.sh <file_of_strings> <iterations>'
    exit 0
fi

g++ -O3 -std=c++11 perf.cc -o perf

./perf $1 $2

./perf.pl $1 $2

