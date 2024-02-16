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
char parse_instructions(char*); //find the opcode, returns instruct type KP
int parse_immediate(char*);
int parse_fuct3(char*);
int parse_fuct7(char*);
int parse_register(char*);

char parse_instructions(char* instr){   //since the Opcode is always the last 7 bits, we can easily extract them
    char opCode[opCodeSz];
    char R[] = "0110011";
    char I[] = "0010011";
    char S[] = "0100011";
    char SB[] = "1100011";
    char UJ[] = "1101111";
    
    for(int i = instrSz - opCodeSz; i < instrSz; i++) { 
        opCode[i-25] = instr[i]; 
        //printf("%i\n", i); //is iteration happening as expected? JLP
    }

    //printf("%s\n", opCode); // is opCode correct?

    if(strcmp(opCode , R) == 0) {            //Which type is it? JLP
        return 'R';
    }
    else if(strcmp(opCode, I) == 0) {
        return 'I';
    }
    else if(strcmp(opCode, S) == 0){
        return 'S';
    }
    else if(strcmp(opCode, SB) == 0){
        return 'B';                         //Note: this is our shorthand for SB JLP
    }
    else if(strcmp(opCode, UJ) == 0){
        return 'U';                         //Note: this is our shorthand for UJ JLP
    }

    printf("%s\n", "Invalid Code");         
     return 'Z';                            //Note: shorthand for invalid code JLP
}


void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz];
    
    printf("Enter an instruction: ");

    fgets(instr, sizeof(instr)+1, stdin);

    //echo the data for now
    printf("%s\n", instr);

    //call parse_instruction print return symbol for now.
    printf("%c\n",parse_instructions(instr));
    
}