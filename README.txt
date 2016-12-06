To run our simulator you just need to type:
 ./sim.sh page_size win_size chosen_sort

Where page_size and win_size are variables that will be passed into our init() function
and chosen_sort is a string matching any of the following lines:
"heapsort", "heapsort.c", "quicksort", "quicksort.c"

The chosen sorting algorithm will be compiled and ran as an executable.

To clean the directory you can either type make clean, or ./sim.sh clean

Upon running you will get a prompt to enter a variable number of keys to sort, then a list
of working set sizes will be printed, along with the average working set size.
