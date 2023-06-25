#include<stdio.h>
#include<stdlib.h>

#define TAPE_LENGTH 10


void get_matching_paranthesis(char** c, char* begin);
void get_input(int** p);
void increment_pointed_by(int** p, int i);;
void move_pointer_left(int** p);;
void move_pointer_right(int** p);;
void print(int** p);
void parse(char** charp, int** intp);

void parse(char** charp, int** intp){
	char* begin = (*charp);
	int* p = *intp;
	while((**charp) != '\0'){

		switch((**charp)){
			case '[':
				if((**intp) == 0){get_matching_paranthesis(charp,begin);}
				break;
			case ']':
				if((**intp) != 0){get_matching_paranthesis(charp,begin);}
				break;
			case '+':
				increment_pointed_by(intp,1);
				break;
			case '-':
				increment_pointed_by(intp,-1);
				break;
			case '>':
				move_pointer_right(intp);
				break;
			case '<':
				move_pointer_left(intp);
				break;
			case '.':
				print(intp);
				break;
			case ',':
				get_input(intp);
				break;
			default:
				break;
		}
		(*charp)++;
	}
}


int main(){
	int tape[TAPE_LENGTH];

	for(int i = 0; i < TAPE_LENGTH; i++){
		tape[i] = 0;
	}
	char test[] = " ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";

	char* cp = &test[0];
	int* ip = &tape[0];

	parse(&cp,&ip);

	return 0;
}

void move_pointer_right(int** p){
	(*p)++;
}
void move_pointer_left(int** p){
	(*p)--;
}

void increment_pointed_by(int** p, int i){
	(**p) += i;
	if(**p >= 256){**p = 0;}
	if(**p <= -1){**p = 255;}
}

void print(int** p){printf("%c",**p);}

void get_input(int** p){ 
	(**p) = getc(stdin);
}

void get_matching_paranthesis(char** c, char* begin){
	int counter = 0;
	if((**c) == ']'){
		counter = 1;
		while(counter != 0){
			(*c)--;
			if(*(c) < begin){
				printf("in proper loop formation");
				exit(1);
			}
			if((**c) == ']'){
				counter++;
			}
			else if((**c) == '['){
				counter--;
			}
		}
	}
	else if((**c) == '['){
		counter = -1;
		while(counter != 0){
			(*c)++;
			if(*(c) == '\0'){
				printf("in proper loop formation");
				exit(1);
			}
			if((**c) == ']'){
				counter++;
			}
			else if((**c) == '['){
				counter--;
			}
		}
	}
}
