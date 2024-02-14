#include <stdio.h>               
#include <string.h>   
                        //define the field sizes to avoid magic numbers JLP
const int instrSz = 32;    
const int opCodeSz = 7; 
const int funct3Sz = 3;
const int funct7Sz = 7;
const int rdSz = 5; 
const int rsSz = 5; 
const int ImmI = 5; 
const int ImmSz2 = 16; 

void print_instructions(char*); //main function will call subfunctions KP
char* parse_instructions(char*); //find the opcode, returns instruct type KP
int parse_immediate(char*);
int parse_fuct3(char*);
int parse_fuct7(char*);
int parse_register(char*);

char* parse_instructions(char* instr){   //since the Opcode is always the last 7 bits, we can easily extract them
    char opCode[opCodeSz];
    char R[] = "0110011";
    char I[] = "0010011";
    char S[] = "0100011";
    char SB[] = "1100011";
    char UJ[] = "1101111";
    
    for(int i = instrSz - opCodeSz; i < instrSz; i++) {
        opCode[i-25] = instr[i]; 
    }

    printf("%s\n", opCode);

    if(strcmp(opCode , R)) {
        return "R";
    }
    if(strcmp(opCode, I)) {
        return "I";
    }
    if(strcmp(opCode, S)){
        return "S";
    }
    if(strcmp(opCode, SB)){
        return "SB";
    }
    if(strcmp(opCode, UJ)){
        return "UJ";
    }

    return "Invalid Code";
}


void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz];
    
    printf("Enter an instruction: ");

    fgets(instr, sizeof(instr)+1, stdin);

    //echo the data for now
    printf("%s\n", instr);

    printf("%s\n",parse_instructions(instr));
    
}