#include <stdio.h>
#include <time.h>
#include "simulator.h"


int psize;
int winsize;

//Max heap for our sort
unsigned int max (unsigned int n, unsigned int i, unsigned int j, unsigned int k) {
    unsigned int m = i;
    if (j < n && get(j) > get(m)) {
        m = j;
    }
    if (k < n && get(k) > get(m)) {
        m = k;
    }
    return m;
}
 
//Down heap for our sort
void downheap (unsigned int n, unsigned int i) {
    while (1) {
        unsigned int j = max(n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }

        int t = get(i);
        put (i, get(j));
        put (j, t);
        i = j;
    }
}
 
// Base of our heapsort
void heapsort (unsigned int n) {
    unsigned int i;
    for (i = (n - 2) / 2;(int) i >= 0; i--) {
        downheap(n, i);
    }
    for (i = 0; i < n; i++) {
        int t = get(n-i-1);
        put ((n-i-1), get(0));
        put (0, t);
        downheap(n - i - 1, 0);
    }
}

//Process function which takes in a number of keys to sort, randomizes the values and then stores them in our hash table
void process()
{
    srand(time(NULL));
    unsigned int i, j, k, t, min, f;
    unsigned int N;
	printf("Please enter the number of keys to sort: ");
    scanf ("%d", &N);
    printf("Sorting %d keys\n", N);

    
    init(psize, winsize);

    for (i = 0; i < N; i++)
    {
        put (i, rand());
    }


    heapsort(N);
    done();
}


//Get the page and window size from the input arguments and call process() function
int main(int argc, char *argv[]){

  psize = atoi(argv[1]);
  winsize = atoi(argv[2]);

  process();
}
