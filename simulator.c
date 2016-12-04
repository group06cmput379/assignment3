#include <stdlib.h>
#include <stdio.h>
#include "simulator.h"


int page_size, window_size;
int *pages_accessed;
int next = 0;
int page;

struct linked_list
{
	int key;
	int data;
	struct linked_list *next;
	struct linked_list *previous;

};

typedef struct linked_list llist;
llist* head = NULL;
llist** table;

llist* ll_new(int key, double data)
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


llist* ll_search(llist* head, int key)
{
	for (;head!=NULL;head=head->next)
	{
		if (head->key==key)
			return head;
	}
	return NULL;
}


void ht_insert(llist** table, int size, llist* item)
{
	int key=item->key;
	table[key%size]=ll_insert(table[key%size],item);
}

void ht_delete(llist** table, int size, llist* item)
{
	int key = item->key;
	table[key%size]=ll_delete(table[key%size],item);
}

llist* ht_search(llist** table, int size, int key)
{
	return ll_search(table[key%size],key);
}



void init(int psize, int winsize)
{
	page_size = psize;
	window_size = winsize;
	int size = 512;
	table = malloc(size*sizeof(llist*));

}


int addPageAccessed(int address)
{
	pages_accessed = realloc(pages_accessed, sizeof(int));
	int page = address/page_size;
	pages_accessed[next] = page;
	next = next + 1;
}

void put(unsigned int address, int value)
{

	llist* new =ll_new(address, value);
	ht_insert(table, 512, new);
	addPageAccessed(address);

}




int get(unsigned int address)
{
	llist* searchedNode = ht_search(table, 512, address);
	int value = searchedNode->data;
	addPageAccessed(address);

	return value;
}


void done()
{
	int i = 0;
	int j = 0;
	for (i = 0; i <10; i++)
	{
		int value = get(i);
		printf("%d\n",value);
	}


	// need to finish this still.
	// get the working set size
	// make sure it rounds up always
	int windows = next/window_size; 
	for (j = 0; j < windows; j++)
	{
		for (i == 0; i < window_size; i++)
		{
			
		}
	}

}





int main(){}