//******************************************
//parse_instructions takes a char* arg, the instruction
//entered by the user, and parses the last 7 digits (binary)
//then recognizes its type. When the type is recognized, a
//single char is returned for printing in the print function
//Called by: print function (later)
//******************************************

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
