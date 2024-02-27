#include <stdio.h>               
#include <string.h>   
#include "definitions.h"
#include "functions.h"


void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz + 1];
    
    printf("Enter an instruction: ");

    fgets(instr, instrSz + 1, stdin);

    print_instructions(instr);

    
}