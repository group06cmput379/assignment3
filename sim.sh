#!/bin/bash

set -e

psize=$1
winsize=$2

if [ $3 = "quicksort" ]; then
    make quicksort
    ./quicksort
elif [ $3 = "heapsort" ]; then
    make heapsort
    ./heapsort
fi


