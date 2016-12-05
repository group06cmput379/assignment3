#include <stdio.h>
#include <time.h>
#include "simulator.h"


static int psize;
static int winsize;

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
 
void heapsort (unsigned int n) {
    unsigned int i;
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
    srand(time(NULL));
    unsigned int i, j, k, t, min, f;
    unsigned int N;
    scanf ("%d", &N);
    printf("Sorting %d keys\n", N);

    
    init (128, 1000);
    printf("Made it\n");

    for (i = 0; i < N; i++)
    {
        printf("%d\n",i);
        put (i, rand());
    }


    heapsort(N);
    done();
}



int main(int argc, char *argv[]){

  //psize = atoi(argv[1]);
  //winsize = atoi(argv[2]);

  process();
}