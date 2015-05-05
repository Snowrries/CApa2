#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*argv[0] is the Circuit Description File
  argv[1] is the Input Values File
  */
	struct entree{
		char name;
		int value;
	};
  	typedef struct entree* entry;


	/*It's definitely possible to go from binary to grey sequencing to decimal.*/
int binary_to_gs_to_dec(entry gatesin[], int numin){
	int i;
	int inpu = 0;
	for(i = 0; i < numin; i++){
		inpu = inpu << 1;
		inpu += gatesin[i]->value;
	}
	for(i = 0; i < (numin << 1); i++){
		if(inpu == (i^(i>>1))){//Check against the grey sequence.
			return i;
		}
	}
	return 0;
}

int find(entry array, char target, int saiz){
	int i;
	for(i = 0; i < saiz; i++){
		//printf("target: %c, name: %c\n", target, array[i].name);
		if(target == (array[i]).name){
			return i;
		}
	}
	return -1;
}
/*Reads variables and sets up values in temporary, or output vars. Use to perform gate operation in main.*/
void read(FILE* cdf, int inno, int outno, entry gatein[], entry gateout[], entry inputs, entry outputs, int *cursize_addr, int numin, int numout){
	int a;
	int b;
	int c;
	char in;
	char out;
	int cursize;
	cursize = *cursize_addr;
	a = 0;
	b = 0;
	c = -1;
	while(a < numin){
		if (fscanf(cdf, " %c", &in) != 1){
			perror("Could not read input");
			exit(1);
		}
	//	printf("in: %c\n", in);
		if((c = find(inputs, in, cursize)) == -1){
			if((c = find(outputs, in, outno)) == -1){
				perror("Could not find input");
				exit(1);
			}
			else{
				gatein[a] = &outputs[c];
			}
		}
		else{
			gatein[a] = &inputs[c];
		}
		a++;
	}
	while(b < numout){
		if(fscanf(cdf, " %c", &out) != 1){
			perror("Could not read output");
			exit(1);
		}
		if((c = find(outputs, out, outno)) == -1){
			if((c = find(inputs, out, cursize)) == -1){
				inputs[cursize].name = out;
				gateout[b] = &inputs[cursize];
				cursize++;
			}
			else{
				gateout[b] = &inputs[c];
			}
		}
		else{
			gateout[b] = &outputs[c];
		}
		b++;
	}
	*cursize_addr = cursize;
	
}
/*
void entryinit(entry wibble){
	wibble.name = 'z';
	wibble.value = 0;
}
*/

int main(int argc, char* argv[]){
	char in;
	char trash[256];
	char *buffer;
	//That's space for all the variables.
	entry inputs;
	entry gatein[52];
	entry gateout[52];
	entry outputs;
	inputs = (entry)malloc(sizeof(struct entree)*52);
//	gatein = (entry)malloc(sizeof(struct entree)*52);
//	gateout = (entry)malloc(sizeof(struct entree)*52);
	outputs = (entry)malloc(sizeof(struct entree)*26);
	//inputs size
	int cursize;
	//Number of inputs, number of outputs.
	int inno;
	int outno;
	int mux[64];
	unsigned int i;
	int numin;
	int numout;
	int test;
	if(argc != 3 && argc != 4){//autograder has weird inputs?
		printf("Incorrect number of arguments.\n");
		exit(1);
	}
	FILE *cdf;
	FILE *ivf;
	/*entryinit(inputs);
	entryinit(outputs);
	entryinit(gateout);
	entryinit(gatein);*/
	cursize = 0;
	buffer = malloc(sizeof(char)*12);
	
	if((cdf = fopen(argv[1], "r")) == NULL){
		perror("Could not open Circuit Description File.");
		exit(1);
	}
	else if((ivf = fopen(argv[2], "r")) == NULL){
		perror("Could not open Input Values File.");
		exit(1);
	}
	
/*	if((cdf = fopen("test1.txt", "r")) == NULL){
		perror("Could not open Circuit Description File.");
		exit(1);
	}
	else if((ivf = fopen("input1.txt", "r")) == NULL){
		perror("Could not open Input Values File.");
		exit(1);
	}
	*/
	while(fscanf(cdf, "%s", buffer)!= EOF){
		if(strcmp(buffer, "INPUTVAR") == 0){
			if (fscanf(cdf, "%d", &inno) != 1){
				perror("Could not read inno");
				exit(1);
			}
			for(i = 0; i < inno; i++){
				if(fscanf(cdf, " %c", &(inputs[i].name)) != 1){
					perror("Could not read all input variables.");
					exit(1);
				}
			}
			cursize = inno;
			/*Finished setting up all initial input variables.
			Temporary ones will be set up as we go.*/
		}

		else if(strcmp(buffer, "OUTPUTVAR") == 0){
			if (fscanf(cdf, "%d", &outno) != 1){
				perror("Could not read outno");
				exit(1);
			}
			//printf("outno:%d\n", outno);
			for(i = 0; i < outno; i++){
				if(fscanf(cdf, " %c", &(outputs[i].name)) != 1){
					perror("Could not read all output variables.");
					exit(1);
				}
			}
			/*Finished setting up all output variables.*/
		}
		else{
			fgets(trash, 200, cdf);
		}
	}
	/*Begin loading values.*/
	/*while(fscanf(ivf, "%d", &(inputs[0].value)) != EOF){
		for(i = 1; i < inno; i++){
			if(fscanf(ivf, " %d", &(inputs[i].value)) != 1){
				perror("Couldn't grab inputs values.");
				exit(1);
			}
			
		}*/
	while(fscanf(ivf, "%d", &test) != EOF){
		//printf("test: %d\n", test);
		inputs[0].value = test;
		for(i = 1; i < inno; i++){
			if(fscanf(ivf, " %d", &test) != 1){
				perror("Couldn't grab inputs values.");
				exit(1);
			}
			inputs[i].value = test;
			//printf("test: %d\n", test);	
		}
	/*Execute circuit.*/
		rewind(cdf);
		while(fscanf(cdf, "%s", buffer)!= EOF){
			//printf("buffer: %s\n", buffer);
			if(strcmp(buffer, "NOT") == 0){
				numin = 1;
				numout = 1;
				read(cdf, inno, outno, gatein, gateout, inputs, outputs, &cursize, numin, numout);
				(gateout[0]->value) = !(gatein[0]->value);
			}
			else if(strcmp(buffer, "AND") == 0){
				numin = 2;
				numout = 1;
				read(cdf, inno, outno, gatein, gateout, inputs, outputs, &cursize, numin, numout);
				(gateout[0]->value) = (gatein[0]->value) && (gatein[1]->value);
				//printf("%c && %c = %d", gatein[0]->name, gatein[1]->name, gateout[0]->value);
			}
			else if(strcmp(buffer, "OR") == 0){
				numin = 2;
				numout = 1;
				read(cdf, inno, outno, gatein, gateout, inputs, outputs, &cursize, numin, numout);
				(gateout[0]->value) = (gatein[0]->value) || (gatein[1]->value);
				//printf("%c || %c = %d", gatein[0]->name, gatein[1]->name, gateout[0]->value);
			}
			else if(strcmp(buffer, "DECODER") == 0){
				if (fscanf(cdf, "%d", &numin) != 1){
					perror("Could not read numin");
					exit(1);
				}
				numout = numin << 1 ;
				read(cdf, inno, outno, gatein, gateout, inputs, outputs, &cursize, numin, numout);
				for(i = 0; i < numout; i++){
					gateout[i]->value = 0;
				}
				gateout[binary_to_gs_to_dec(gatein, numin)]->value = 1;
				
			}
			else if(strcmp(buffer, "MULTIPLEXER") == 0){
				if (fscanf(cdf, "%d", &numin) != 1){
					perror("Could not read numin");
					exit(1);
				}
				if(numin > 64){
					perror("Buffer overflow protection. We can only take 64 inputs in the multiplexer.");
					exit(1);
				}
				for(i = 0; i < numin; i++){
					if(fscanf(cdf, " %d", &test) != 1){
						if(fscanf(cdf, " %c", &in)!= 1){
							perror("Trouble reading mux inputs.");
							exit(1);
						}
						else{
							printf("Mux char input: %c\t", in);
							if((test = find(inputs, in, cursize)) == -1){
								if((test = find(outputs, in, cursize)) == -1){
									perror("Could not find mux input.");
									exit(1);
								}
								// found in outputs
								else{
									mux[i] = outputs[test].value;
								}
							}//found in inputs.
							else{
								mux[i] = inputs[test].value;
							}
						}
					}
					else{
						printf("Mux number input: %d\t", test);
						mux[i] = test;
					}
					printf("mux[%d]: %d\n", i, mux[i]);
				}
				numin = numin >> 1;
				numout = 1;
				read(cdf, inno, outno, gatein, gateout, inputs, outputs, &cursize, numin, numout);
				printf("Mux selects: ");
				for(i = 0; i < numin; i++){
					printf("%d", gatein[i]->value);
				}
				printf("\n");
				gateout[0]->value = mux[(binary_to_gs_to_dec(gatein, numin))];
			}
			else{//hopefully eats the line
				fgets(trash, 200, cdf);
			}
		}
		for(i = 0; i < (outno-1); i++){
			printf("%d ", outputs[i].value);
		}
		printf("%d\n", outputs[(outno-1)].value);
		
	}
	return 0;
}

