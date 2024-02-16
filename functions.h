
//******************************************
//parse_instructions takes a char* arg, the instruction
//entered by the user, and parses the last 7 digits (binary)
//then recognizes its type. When the type is recognized, a
//single char is returned for printing in the print function
//Called by: print function (later)
//Argument: char* instr user entered instruction
//Returns: char representing the OpCode
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
    else if(strcmp(opCode, S) == 0) {
        return 'S';
    }
    else if(strcmp(opCode, SB) == 0) {
        return 'B';                         //Note: this is our shorthand for SB JLP
    }
    else if(strcmp(opCode, UJ) == 0) {
        return 'U';                         //Note: this is our shorthand for UJ JLP
    }

    printf("%s\n", "Invalid Code");         
     return 'Z';                            //Note: shorthand for invalid code JLP
}

//******************************************
//parse_funct3 takes a char* arg, the instruction
//entered by the user, and parses 3 digits (binary) 12 -14
//then recognizes the funct3 code. When the code is recognized, a
//single int is returned for intrepretation in the print function
//Called by: print function (later)
//Argument: char* instr
//Returns: int represents the funct3 code
//******************************************

int parse_funct3(char* instr) {
    int j = 0;
    char funct3[] ="000";                                   //will hold extracted funct code JLP
    int start = instrSz - (opCodeSz + funct3Sz + rdSz);     //starts loop at start of funct3 code JLP
    
    char zero[] = "000";
    char one[] = "001";
    char two[] = "010";
    char three[] = "011";
    char four[] = "100";
    char five[] = "101";
    char six[] = "110";
    char seven[] = "111";

    for(int i = start; i < 20; i++) {                       //extract the funct3 code JLP
        funct3[j] = instr[i];
        j++;
    }
    printf("%s\n", "Funct3 Code:");
    printf("%s\n", funct3);                 //For testing puroses JLP

    //return the decimal number to print or another function 
    //will deal with what that means JLP
    if(strcmp(funct3,zero) == 0) {
        return 0;
    }
    else if(strcmp(funct3, one) == 0) {
        return 1;
    }
    else if(strcmp(funct3, two) == 0) {
        return 2;
    }
    else if(strcmp(funct3, three) == 0) {
        return 3;
    }
    else if(strcmp(funct3, four) == 0) {
        return 4;
    }
    else if(strcmp(funct3, five) == 0) {
        return 5;
    }
    else if(strcmp(funct3, six) == 0) {
        return 6;
    }
    else if(strcmp(funct3, seven) == 0) {
        return 7;
    }

    return 8;                               //Indicates failure, should not be this big JLP
}