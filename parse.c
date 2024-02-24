#include <stdio.h>               
#include <string.h>   
#include "definitions.h"
#include "functions.h"


void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz];
    
    printf("Enter an instruction: ");

    fgets(instr, sizeof(instr) + 1, stdin);

    //echo the data for testing JLP
    printf("%s\n", instr);

    //call parse_instruction print return symbol for now.
    printf("%c\n",parse_instructions(instr));

    //call parse_funct3 and print the decimal value of it for now.
    printf("%i\n", parse_funct3(instr));
    
    printf("%i\n", parse_funct7(instr));

    printf("%i\n", parse_immediate(instr));
}