#ifndef count_H
#define count_H
#include <stdio.h>
#include <stdlib.h>
struct Node{
	size_t* data;
	      struct Node *next;
};
typedef struct Node * nodeptr;

struct hashtable_with_chaining{
	nodeptr keys[];
	int rc;
	/*Stands for running count*/
};
typedef struct hashtable_with_chaining* hash;


hash HashCreate(int size){
	hash Kira;
	int i;
}

void AddValue(size_t address, hash hashtable){
	int key;
	nodeptr noo;
}

/*returns 1 if the address is already in the table.
  returns 0 if it isn't.
 */
int exists(size_t address, hash hashtable, int key){
	nodeptr inc;
}
void freedom(hash hashtable, int size){
	int i;
	nodeptr del;
}


#endif