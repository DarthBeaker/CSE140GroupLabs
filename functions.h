
//******************************************
//parse_instructions takes a char* arg, the instruction
//entered by the user, and parses the last 7 digits (binary)
//then recognizes its type. When the type is recognized, a
//single char is returned for printing in the print function
//Called by: parse_immediate function, print function (later)
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
    //lui and andi are both U, and they have different opcodes...
    
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
    else if(strcmp(opCode, "0010111")) {
        return 'A';                         //for auipc
    }
    else if(strcmp(opCode, "0110111")) {
        return 'L';                         //for lui
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



//******************************************
//parse_funct7 takes a char* arg, the instruction
//entered by the user, and parses 7 digits (binary) 25-31
//then recognizes the funct3 code. When the code is recognized, a
//single int is returned for intrepretation in the print function
//Called by: print function (later)
//Argument: char* instr
//Returns: int represents the funct7 code
//******************************************
int parse_funct7(char* instr){
    const int funct7_size = 7;
    const int funct7_start = 25;
    int funct7_dec_val = 0;
    int binary_bit_value = 1;
    for(int i = funct7_start; i < instrSz; i++){
        if(instr[instrSz - i - 1] == '0'){
            binary_bit_value *= 2;
        }else{
            funct7_dec_val += binary_bit_value;
            binary_bit_value *= 2;
        }
    };

    return funct7_dec_val;
}


/*
//parse_immediate takes a char* arg, the instruction
//entered by the user, and parses ? digits depending on 
//what instruction type it is
//Called by: print function (later)
//Argument: char* instr, ? might need second arg for instruction type ?
//Returns: int represents the immediate
*/
int parse_immediate(char* instr){
    char op = parse_immediate(instr);

    if(op == 'R') {
        return -1;                  //indicates no immediate used JLP
    }
    else if(op == 'I') {
        //call sub parse_Imm_I(instr);
    }
    else if(op == 'S' || op == 'B') {
        //call function parse_Imm_S(instr);
        //is similar to SB
    }
    else if(op == 'A' ||op == 'L' || op == 'U') {
        //call function parse_Imm_U(instr);
        //covers U & UJ
    }
    
    return -1;              //indicates no go
}







//******************************************
//parse_register will take a char arg and then
//read the register value and return the int associated with the c-string of binary
//might want to also pass what specific register we're trying to read if passing the
//full instruction or we could in the main function break it up into registers
//based on instruction type and just have this function read them and return the proper
//int to be printed
//******************************************
int parse_register(char* instr){

 
}