#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TAPE_LENGTH 100
#define RUN_FILE_COMMAND "-f"

//given either [ or ] moves the char* pointed by c to the location of the corrosponding square brace
void get_matching_paranthesis(char** c, char* begin);
//simply reads an input char and stores it as an int to the location pointed by p
void get_input(int* p);
//increments or decrements the value pointed by a pointer to which p points
//if the resultant value is greater than 255, new value is 0
//if the resultant value is less than 0, new value is 255
void increment_pointed_by(int* p, int i);;
//moves pointer to left or right
void move_pointer_left(int** p);;
void move_pointer_right(int** p);;

//prints the value
void print(int* p);
//given a char array that contains bf commands, runs the instructions given
void parse(char** charp, int** intp);
//gets how many bf commands are present in a file (can be any extention)
//allows for commands (which are all characters that are not one of 8 bf commands)
//also deals with weather or not the file exists
int get_char_amount(char file_name[]);
//same as parse, the difference is reads the file name of which is given by the parameter
//and parses the relevant chars in that file
void parse_file_named(char file_name[]);
//shell mode
void shell();



int main(int argc, char* argv[]){
	if(argc == 1){
		shell();
	}
	else if(strcmp(argv[1],RUN_FILE_COMMAND) == 0){
		if(strlen(argv[2]) == 0){
			printf("you must enter a file to interpret\n");
			printf("type 'bf_interpreter' followed by 'help' to learn more about command line options");
		}
		else{
			parse_file_named(argv[2]);
		}
	}
	else{
		printf("command unknown\n");
		printf("type 'bf_interpreter' followed by 'help' to learn more about command line options");
		return 1;
		return 1;
	}

	return 0;
}

const char RUN[] = "run";//run a file
const char EXE[] = "exe";//execute a command
const char HELP[] = "help";//display potantial commands
const char QUIT[] = "quit";//quit the program

void shell(){
	int is_running = 1;
	while(is_running){
		char command[50];
		printf(">brainfuck shell> ");
		scanf("%s",&command[0]);

		if(strcmp(command,RUN) == 0){
			char file_name[strlen(command) - strlen(RUN)];
			scanf("%s",&file_name[0]);
			parse_file_named(file_name);
		}
		else if(strcmp(command,EXE) == 0){
			//for testing purposes 200 bf commands should be enough
			char code[200];
			scanf("%s",code);
			int tape[TAPE_LENGTH];

			for(int i = 0; i < TAPE_LENGTH; i++){tape[i] = 0;}

			int* tape_p = &tape[0];
			char* code_p = &code[0];

			parse(&code_p,&tape_p);

		}
		else if(strcmp(command,QUIT) == 0){
			is_running = 0;
			break;
		}
		else if(strcmp(command,HELP) == 0){
			printf("HELP SCREEN\n-----------\n");
			printf("Command line arguments:\n");
			printf("\tbf_interpreter.exe -f <file name> -> runst the file indicated by <file name>\n");
			printf("\tbf_interpreter.exe -> runst the program in shell mode\n");
			printf("Shell mode:\n");
			printf("\trun <file_name> -> runs the file that has the name <file_name>\n");
			printf("\tquit -> terminates shell mode\n");
			printf("\texe <code> -> runst the brainfuck code given\n");
			printf("\thelp -> displays this menu\n");
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

void increment_pointed_by(int* p, int i){
	(*p) += i;
	if(*p >= 256){*p = 0;}
	if(*p <= -1){*p = 255;}
}

void print(int* p){printf("%c",*p);}

void get_input(int* p){ 
	(*p) = getc(stdin);
}

void get_matching_paranthesis(char** c, char* begin){
	//characters [ and ] are given values -1 and 1 respectively, which is compeletely arbetary
	//this algorithm would work as long as the absolute values associated with the characters are equal
	//depending on the paranthesis, the loops below will move the pointer in the parameter forward or backward
	//at the begining when there is a simple parantehesis, there must be a matchin one
	//since the matching one has the negative value of the initial one, once the matching paranthesis is found, the counter should be 0
	//[[[[]]]]
	//^ start from here
	//counter is 1
	//[[[[]]]]
	// ^
	//counter is 2
	//[[[[]]]]
	//  ^
	//counter is 3
	//[[[[]]]]
	//   ^
	//counter is 4
	//[[[[]]]]
	//    ^
	//counter is 3, the last [ is closed
	//[[[[]]]]
	//     ^
	//counter is 2
	//[[[[]]]]
	//      ^
	//counter is 1
	//[[[[]]]]
	//       ^
	//counter is 0
	//if either the end of the string (\0 or null character) is reached before counter hits 0, there is a problem with the paranthesis, the program panics and terminates
	//if the pointer c points to a lesser location than the begin pointer, there is a problem with the parantehesis

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
	//itterates over the char array pointed by the pointer pointed to by charp
	//based on the chars either does the corrosponding actions (increment the value @ intp, move pointer to left etc) or does nothing (the character is part of a comment)
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
				increment_pointed_by(*intp,1);
				break;
			case '-':
				increment_pointed_by(*intp,-1);
				break;
			case '>':
				move_pointer_right(intp);
				break;
			case '<':
				move_pointer_left(intp);
				break;
			case '.':
				print(*intp);
				break;
			case ',':
				get_input(*intp);
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
