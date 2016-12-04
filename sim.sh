#!/bin/bash

set -e

if [ $1 = "clean" ]; then
    make clean
elif [ $3 = "heapsort" ] || [ $3 = "heapsort.c" ]; then
    make heapsort
    ./heapsort $1 $2
elif [ $3 = "quicksort" ] || [ $3 = "quicksort.c" ]; then
    make quicksort
    ./quicksort $1 $2
fi


