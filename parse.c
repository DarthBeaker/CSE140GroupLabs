#include <stdio.h>               
#include <string.h>   
#include "definitions.h"
#include "functions.h"


void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz + 1];
    
    printf("Enter an instruction: ");

    fgets(instr, instrSz + 1, stdin);

    //echo the data for testing JLP
    //printf("%s\n", instr);

    //call parse_instruction print return symbol for now.
    printf("Instruction Type: %c\n",parse_instructions(instr));


    //since instructions can have multiple
    //registers it is simplier to print 
    //them all in the function
    parse_register(instr);


    //call parse_funct3 and print the decimal value of it for now.
    printf("Funct3: %i\n", parse_funct3(instr));
    
    printf("Funct7: %i\n", parse_funct7(instr));

    printf("Immediate: %i\n", parse_immediate(instr));
}