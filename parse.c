#include <stdio.h>               
#include <string.h>   
#include "definitions.h"
#include "functions.h"


void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz];
    
    printf("Enter an instruction: ");

    fgets(instr, sizeof(instr)+1, stdin);

    //echo the data for testing JLP
    printf("%s\n", instr);

    //call parse_instruction print return symbol for now.
    printf("%c\n",parse_instructions(instr));
    
}