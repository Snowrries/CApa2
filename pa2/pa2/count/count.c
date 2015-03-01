#include "count.h"

hash HashCreate(int size){
	hash kira;
	int i;
	nodeptr ks;
	kira = (hash)malloc(sizeof(hash));
	ks = (nodeptr)malloc(size*sizeof(nodeptr));
	kira->rc = 0;
	for(i = 0; i <size; i++){
		(kira->keys)[i] = ks;
		ks->data = sizeof(NULL);
		ks->next = NULL;
		ks++;
	}
	return kira;
}
void AddValue(size_t address, hash hashtable){
	int key;
	nodeptr noo;
	key = (int)(address%1000);
	/*If the address is unique, add it.*/
	if(exists(address, hashtable, key)==0){
		noo = malloc(sizeof(nodeptr));
		noo-> data = address;
		noo-> next = hashtable->keys[key];
		hashtable->keys[key] = noo;
		hashtable->rc++;
	}
	/*else, do nothing.*/
}

int exists(size_t address, hash hashtable, int key){
	nodeptr inc;
	inc = hashtable->keys[key];
	while(inc->data != address){
		if(inc->next == NULL){
			return 0;
		}
		inc = inc->next;
	}
	return 1;
}

void freedom(hash hashtable, int size){
	int i;
	nodeptr del;
	for(i = 0; i < size; i++){
		del = hashtable->keys[i];
		while(del!=NULL){
			hashtable->keys[i]= hashtable->keys[i]->next;
			free(del);
			del = hashtable->keys[i]->next;
		}
	}
	free(hashtable);
}


int main(int argc, char** argv) {
	size_t add;
	hash kira;
	FILE* fire;
	if(argc != 2){
		printf("Incorrect number of inputs.");
		return 0;
	}
	kira = HashCreate(1000);
	fire = fopen(argv[1],"r");
	
	while(fscanf(fire,"%zx",&add)!=EOF){
		AddValue(add,kira);
	}
	fclose(fire);
    printf ("%d",kira->rc);
	freedom(kira, 1000);
    return 0;
}
