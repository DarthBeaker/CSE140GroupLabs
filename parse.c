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
    char instruct_type = parse_instructions(instr);
    printf("Instruction Type: %c\n", instruct_type);


    //since instructions can have multiple
    //registers it is simplier to print 
    //them all in the function
    parse_register(instr);


    //call parse_funct3 and print the decimal value of it for now.
    if(instruct_type != 'U'){
        printf("Funct3: %i\n", parse_funct3(instr));
    }
    
    if(instruct_type == 'R'){
        printf("Funct7: %i\n", parse_funct7(instr));
    }
    else{
        printf("Immediate: %i\n", parse_immediate(instr));
    }
}