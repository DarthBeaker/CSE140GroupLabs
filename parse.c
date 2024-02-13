#include <stdio.h>
#define static instrSz = 32;    //number of bits 
#define static opCodeSz = 7; //fix
#define static funct3Sz = 3;
#define static funct7Sz = 7;
#define static rdSz = 5; //
#define static rsSz = 5; //
#define static immI = 5; //check
#define static immSsz5 = 5;
#define static immSsz7 = 7;
#define static immSBsz5 = 5;
#define static immSBsz = 7;
#define static immSz2 = 16; //check 

void print_instructions(char*); //main function will call subfunctions
char parse_instructions(char*); //find the opcode, returns instruct type
int parse_immediate(char*);
int parse_fuct3(char*);
int parse_fuct7(char*);
int parse_register(char*);


int main() {

    return 0;
}