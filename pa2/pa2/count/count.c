#include "count.h"

hash HashCreate(int size){
	kira = malloc(size*sizeof(nodeptr));
	for(i = 0; i <size; i++){
		kira[i]->data = NULL;
		kira[i]->next = NULL;
	}
	
}
void AddValue(*size_t address, hash hashtable){
	key = (int)()address%1000);
	/*If there is nothing in the hashed location,*/
	
	if(hashtable->keys[key] == NULL){
		hashtable->keys[key]-> data = address;
		hashtable->rc++;
	}
	/*If there is something there, but the address is unique,*/
	else if(exists(address, hash, key)==0){
		noo = malloc(sizeof(nodeptr));
		noo-> data = address;
		noo-> next = hashtable->keys[key];
		hashtable->keys[key] = noo;
		hashtable->rc++;
	}
	/*else, do nothing.*/
}

int exists(*size_t address, hash hashtable){
	inc = hashtable->keys[key];
	while(strcmp(inc->data,address) != 0){
		if(inc->next == NULL){
			return 0;
		}
		inc = inc->next;
	}
	return 1;
}

void freedom(hash hashtable, int size){
	for(i = 0; i < size; i++){
		del = hashtable->keys[i]->data;
		while(del->data!=NULL){
			hashtable->keys[i]= hashtable->keys[i]->next;
			free(del);
			del = hashtable->keys[i]->next;
		}
	}
	free(hashtable);
}


int main(int argc, char** argv) {
	size_t* add;
	hash kira;
	FILE* fire;
	if(argc != 2){
		printf("Incorrect number of inputs.");
		return 0;
	}
	kira = HashCreate(1000);
	fire = fopen(argv[1],r);
	
	while(fscanf(fire,"%zx",add)!=EOF){
		AddValue(add,kira);
	}
	fclose(fire);
    printf ("%d",kira->rc);
	freedom(kira, 1000);
    return 0;
}
