#include<stdio.h>
#include<stdlib.h>

#define TAPE_LENGTH 100


void get_matching_paranthesis(char** c, char* begin);
void get_input(int** p);
void increment_pointed_by(int** p, int i);;
void move_pointer_left(int** p);;
void move_pointer_right(int** p);;
void print(int** p);
void parse(char** charp, int** intp);
int get_char_amount(char file_name[]);
void parse_file_named();
void test(char* c);



int main(){
	parse_file_named();

	return 0;
}

void parse_file_named(){
	char file_name[40];
	printf("enter file name : ");
	scanf("%s",file_name);
	int length_of_file = get_char_amount(file_name);
	char file_content[length_of_file+1];

	int tape[TAPE_LENGTH];
	for(int i = 0; i < TAPE_LENGTH; i++){
		tape[i] = 0;
	}


	FILE* file = fopen(file_name,"r");
	for(int i = 0; i < length_of_file;){
		char current_char = fgetc(file);
		switch(current_char){
			case '<':
			case '>':
			case '.':
			case ',':
			case '+':
			case '-':
			case '[':
			case ']':
				file_content[i] = current_char;
				i++;
				break;
			default:
				continue;
		}
	}
	fclose(file);
	file_content[length_of_file] = '\0';
	int* tape_pointer = &tape[0];
	char* code_pointer = &file_content[0];

	parse(&code_pointer,&tape_pointer);

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
int get_char_amount(char file_name[]){
	FILE* file = fopen(file_name,"r");
	int res = 0;
	while(!feof(file)){
		switch(fgetc(file)){
			case '<':
			case '>':
			case '.':
			case ',':
			case '+':
			case '-':
			case ']':
			case '[':
				res++;
				break;
			default:
				continue;
				break;
		}
	}
	fclose(file);
	return res;
}
