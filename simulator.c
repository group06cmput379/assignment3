#include <stdlib.h>
#include <stdio.h>
#include "simulator.h"
#include <math.h>

//setting up our global variables for the simulator
int page_size, window_size;
int *pages_accessed;
int *workingSetSizes;
int *uniquevalues;
int currentWindow = 0;
int currentIndex = 0;
int next = 0;
int page;
unsigned int size;

//basic structure for our doubly linked list (which exists within a hash table to store all values)
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

//Create a new linked list when needed
llist* ll_new(unsigned int key, int data)
{
	llist* new = malloc(sizeof(llist));
	new->key = key;
	new->data = data;
	new->next=NULL;

	return new;
}

//Insert a node into an existing list
llist* ll_insert(llist* head, llist* new)
{
	new->next = head;
	if (head != NULL)
		head->previous=new;
	head=new;
	return head;
}


//Delete an item from a given list
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

//Search through a list for a specific key (or address)
llist* ll_search(llist* head, unsigned int key)
{
	for (;head!=NULL;head=head->next)
	{
		if (head->key==key)
			return head;
	}
	return NULL;
}

//Insert an item into a linked list of a specific hash table entry
void ht_insert(llist** table, unsigned int size, llist* item)
{
	unsigned int key=item->key;
	table[key%size]=ll_insert(table[key%size],item);
}

//Delete an item from the linked list of a specific hash table entry
void ht_delete(llist** table, unsigned int size, llist* item)
{
	unsigned int key = item->key;
	table[key%size]=ll_delete(table[key%size],item);
}

//Search for an item in the hash table
llist* ht_search(llist** table, unsigned int size, unsigned int key)
{
	return ll_search(table[key%size],key);
}


//Initializing space for our parameters given when the program is executed
//We chose a table size of 2^20 to try and keep our linked lists relatively small (avoid deep searches)
void init(int psize, int winsize)
{
	page_size = psize;
	window_size = winsize;
	size = 524288;
	table = malloc(size*sizeof(llist*));
	pages_accessed = (int*) malloc (sizeof(int));
		//workingSetSizes = (int *) malloc (sizeof(int));

}


//Keep track of a page by adding it to an array and reallocating memory for a new page
void addPageAccessed(unsigned int address)
{

	pages_accessed = (int*)realloc(pages_accessed, (next+1)*sizeof(int));
	int page = (int) address/page_size;

	pages_accessed[next] = page;
	next = next + 1;
}

//Puts a random value into an address in the hash table
void put(unsigned int address, int value)
{

	llist* new =ll_new(address, value);
	ht_insert(table, size, new);
	addPageAccessed(address);

}

//Gets a specific value from our hash table
int get(unsigned int address)
{
	llist* searchedNode = ht_search(table, size, address);
	int value = searchedNode->data;
	addPageAccessed(address);

	return value;
}

//If we've accessed a new page for the first time, add it to an array
//If the page has already been accessed, ignore it
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

//Clean up the simulator when all of the work has been done. Return necessary information about the simulator and free memory
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

	//Returns the average working set size
	double average = (double)total /(double)windows;
	printf ("%f\n", average);

}



