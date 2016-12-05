#include <stdlib.h>
#include <stdio.h>
#include "simulator.h"
#include <math.h>


int page_size, window_size;
int *pages_accessed;
int *workingSetSizes;
int *uniquevalues;
int currentWindow = 0;
int currentIndex = 0;
int next = 0;
int page;
unsigned int size;

struct linked_list
{
	unsigned int key;
	int data;
	struct linked_list *next;
	struct linked_list *previous;

};

typedef struct linked_list llist;
llist* head = NULL;
llist** table;

llist* ll_new(unsigned int key, int data)
{
	llist* new = malloc(sizeof(llist));
	new->key = key;
	new->data = data;
	new->next=NULL;

	return new;
}

llist* ll_insert(llist* head, llist* new)
{
	new->next = head;
	if (head != NULL)
		head->previous=new;
	head=new;
	return head;
}



llist* ll_delete(llist*head, llist* item)
{
	if (item->previous!=NULL)
		item->previous->next=item->next;
	if (item->next!=NULL)
		item->next->previous=item->previous;
	if (item==head)
		head=item->next;
	return head;
}


llist* ll_search(llist* head, unsigned int key)
{
	for (;head!=NULL;head=head->next)
	{
		if (head->key==key)
			return head;
	}
	return NULL;
}


void ht_insert(llist** table, unsigned int size, llist* item)
{
	unsigned int key=item->key;
	table[key%size]=ll_insert(table[key%size],item);
}

void ht_delete(llist** table, unsigned int size, llist* item)
{
	unsigned int key = item->key;
	table[key%size]=ll_delete(table[key%size],item);
}

llist* ht_search(llist** table, unsigned int size, unsigned int key)
{
	return ll_search(table[key%size],key);
}



void init(int psize, int winsize)
{
	page_size = psize;
	window_size = winsize;
	size = 1048576;
	table = malloc(size*sizeof(llist*));
	pages_accessed = (int*) malloc (sizeof(int));
		//workingSetSizes = (int *) malloc (sizeof(int));

}






void addPageAccessed(unsigned int address)
{

	pages_accessed = (int*)realloc(pages_accessed, (next+1)*sizeof(int));
	int page = (int) address/page_size;

	pages_accessed[next] = page;
	next = next + 1;
}


void put(unsigned int address, int value)
{

	llist* new =ll_new(address, value);
	ht_insert(table, size, new);
	addPageAccessed(address);

}




int get(unsigned int address)
{
	llist* searchedNode = ht_search(table, size, address);
	int value = searchedNode->data;
	addPageAccessed(address);

	return value;
}




int addToUniqueArray(int page, int index)
{
	int exists = 0;
	int i = 0;
	for (i = 0; i < index; i++)
	{
		//printf("unique : %d\n",uniquevalues[i]);
		if (page == uniquevalues[i])
		{
			exists = 1;
			break;
		}
	}
	if (exists==0)
	{
		index = index + 1;
		uniquevalues = (int*) realloc(uniquevalues, (index)*sizeof(int));
		uniquevalues[index-1] = page;
	}

	return index;

}


void done()
{
	int i = 0;
	int j = 0;

	int windows = (next/window_size)+1;


	workingSetSizes = (int*) malloc(windows*sizeof(int));

	int currentIndex = 0;
	int currentsize = window_size;
	int total =0;
	for (i =0; i <windows; i++)
	{

		uniquevalues = (int *) malloc(1*sizeof(int));

		int sizeofuniquearray = sizeof(uniquevalues)/sizeof(int);
		int index = 0;
		for (j = currentIndex; j < currentsize; j ++)
		{
			if (j >= next)
			{
				break;
			}
			int page = pages_accessed[j];
			if (j == currentIndex)
			{
				uniquevalues = (int*) realloc(uniquevalues, (index+1)*sizeof(int));
				uniquevalues[index] = page;
				index = index + 1;
			}
			index = addToUniqueArray(page, index);
		}

		currentIndex = currentsize;
		currentsize = currentsize + window_size;
		int workingsetsize = sizeof(uniquevalues)/sizeof(int);

		free(uniquevalues);
		printf("Working set size: %d\n",index);
		total = total + index;

	}
	double average = (double)total /(double)windows;
	printf ("%f\n", average);

}



