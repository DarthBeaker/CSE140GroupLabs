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

    
<<<<<<< Updated upstream
=======
    if(instruct_type == 'R'){
        printf("Funct7: %i\n", parse_funct7(instr));
    }
    else{
        printf("Immediate: %i\n", parse_immediate(instr));
    }
    print_all(instr);

>>>>>>> Stashed changes
}