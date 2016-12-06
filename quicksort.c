#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "simulator.h"

static int psize;
static int winsize;

//Swap a smaller value with a larger value
void swap(unsigned int i, unsigned int j){
  int temp = get(i);
  put(i, get(j));
  put(j, temp);
}

//In-place partitioning of the elements 
unsigned int partition(unsigned int left, unsigned int right){
  unsigned int begin, end, i;
  int pivot;
  pivot = get(right);
  begin = left - 1;
  for (i = left; i <= right-1; i++)
    {
      if(get(i)<=pivot)
	{
	  begin++;
	  swap(begin, i);
	}
    }
  swap(begin+1,right);
  return(begin+1);
}

//Sort the different partitions to return all of the elements in ascending order
void quicksort(int begin,int end)
{
  unsigned int q;
  while(begin < end)
    {
      q = partition(begin, end);

      if (q - begin < end - q)
	{
	  quicksort(begin, q-1);
	  begin = q + 1;
	}
      else
	{
	  quicksort(q + 1, end);
	  end = q-1;
	}
    }    	  
}


//Process function takes in a specified number of keys, stores them in our hash table and then sorts them in ascending order using quicksort
void process()
{
  srand(time(NULL));
  unsigned int N, i;
  printf("Please enter the number of keys to sort: ");
  scanf("%d", &N);
  printf("Sorting %d keys\n", N);

  init(psize, winsize);
  
  i = 0;
  for (i=0;i<N;i++)
    {
      put(i, rand());
    }

  quicksort(0, N-1);
  done();
}


//Main function that takes in the page and window sizes via Command Line Arguments and then calls process() function
int main(int argc, char *argv[]){

  psize = atoi(argv[1]);
  winsize = atoi(argv[2]);
  process();
}

