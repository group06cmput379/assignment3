#include <stdio.h>
#include <time.h>
#include "simulator.h"

static int psize;
static int winsize;


int max (int n, int i, int j, int k) {
    int m = i;
    if (j < n && get(j) > get(m)) {
        m = j;
    }
    if (k < n && get(k) > get(m)) {
        m = k;
    }
    return m;
}
 
void downheap (int n, int i) {
    while (1) {
        int j = max(n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }

        int t = get(i);
        put (i, get(j));
        put (j, t);
        i = j;
    }
}
 
void heapsort (int n) {
    int i;
    for (i = (n - 2) / 2; i >= 0; i--) {
        downheap(n, i);
    }
    for (i = 0; i < n; i++) {
        int t = get(n-i-1);
        put ((n-i-1), get(0));
        put (0, t);
        downheap(n - i - 1, 0);
    }
}

void process()
{
    // make sure that i is in unsigned int
    srand(time(NULL));
    int i, N, j, k, t, min, f;
    printf("Please enter number of keys to sort: ");
    scanf ("%d", &N);
    printf("Sorting %d keys\n", N);

    
    init (psize, winsize);
    

    for (i = 0; i < N; i++)
    {
        put (i, rand());
    }


    heapsort(N);
    done();
}


int main (int argc, char *argv[]) {

  psize = atoi(argv[1]);
  winsize = atoi(argv[2]);
  process();

}
