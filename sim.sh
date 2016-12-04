#!/bin/bash

set -e

psize=$1
winsize=$2

if [ $1 = "clean" ]; then
    make clean
elif [ $3 = "heapsort" ] || [ $3 = "heapsort.c" ]; then
    make heapsort
    ./heapsort psize winsize
elif [ $3 = "quicksort" ] || [ $3 = "quicksort.c" ]; then
    make quicksort
    ./quicksort psize winsize
fi


