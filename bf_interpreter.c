#include<stdio.h>
#include<string.h>
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
void parse_file_named(char file_name[]);
void shell();



int main(){
	shell();

	return 0;
}

const char RUN[] = "run";//run a file
const char EXE[] = "exe";//execute a command
const char HELP[] = "help";
const char QUIT[] = "quit";

void shell(){
	while(1){
		char command[50];
		printf(">brainfuck shell> ");
		scanf("%s",&command[0]);

		if(strcmp(command,RUN) == 0){
			char file_name[strlen(command) - strlen(RUN)];
			scanf("%s",&file_name[0]);
			parse_file_named(file_name);
		}
		else if(strcmp(command,EXE) == 0){
			char code[200];
			scanf("%s.",code);
			int tape[TAPE_LENGTH];

			for(int i = 0; i < TAPE_LENGTH; i++){tape[i] = 0;}

			int* tape_p = &tape[0];
			char* code_p = &code[0];

			parse(&code_p,&tape_p);

		}
		else if(strcmp(command,QUIT) == 0){
			break;
		}
		else if(strcmp(command,HELP) == 0){
			printf("HELP SCREEN\n-----------\n");
			printf("run <file_name> -> runs the file that has the name <file_name>\n");
			printf("quit -> terminates shell mode\n");
			printf("exe <code> -> runst the brainfuck code given\n");
			printf("help -> displays this menu\n");
		}
		else{
			printf("command not recognized\n");
		}

	}

}

void parse_file_named(char file_name[]){
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
	if(file == NULL){
		perror("file not found");
		exit(1);
	}
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
