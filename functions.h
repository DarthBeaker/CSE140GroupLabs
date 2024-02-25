
//******************************************
//parse_instructions takes a char* arg, the instruction
//entered by the user, and parses the last 7 digits (binary)
//then recognizes its type. When the type is recognized, a
//single char is returned for printing in the print function
//Called by: parse_immediate function, print function (later)
//Argument: char* instr user entered instruction
//Returns: char representing the OpCode
//******************************************

char parse_instructions(const char* instr){   //since the Opcode is always the last 7 bits, we can easily extract them
    char opCode[opCodeSz];
    
    for(int i = instrSz - opCodeSz; i < instrSz; i++) { 
        opCode[i-25] = instr[i]; 
        //printf("%i\n", i); //is iteration happening as expected? JLP
    }

    //printf("%s\n", opCode); // is opCode correct?
    
          
    if(strcmp(opCode , opCodeLU[0]) == 0) {            //Which type is it? JLP
        return 'R';
    }
    else if((strcmp(opCode, opCodeLU[1]) == 0 ) || (strcmp(opCode, opCodeLU[2]) == 0) || (strcmp(opCode, opCodeLU[3]) == 0)) {
        return 'I';
    }
    else if(strcmp(opCode, opCodeLU[4]) == 0) {
        return 'S';
    }
    else if(strcmp(opCode, opCodeLU[5]) == 0) {
        return 'B';                         //Note: this is our shorthand for SB JLP
    }
    else if(strcmp(opCode, opCodeLU[6]) == 0) {
        return 'J';                         //Note: this is our shorthand for UJ JLP
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

int parse_funct3(const char* instr) {
    int j = 0;
    char funct3[] ="000";                                   //will hold extracted funct code JLP
    int start = instrSz - (opCodeSz + funct3Sz + rdSz);     //starts loop at start of funct3 code JLP

    for(int i = start; i < 20; i++) {                       //extract the funct3 code JLP
        funct3[j] = instr[i];
        j++;
    }
    //printf("%s\n", "Funct3 Code:");
    //printf("%s\n", funct3);                 //For testing puroses JLP

    //return the decimal number to print or another function 
    //will deal with what that means JLP
    if(strcmp(funct3,f3LU[0]) == 0) {
        return 0;
    }
    else if(strcmp(funct3, f3LU[1]) == 0) {
        return 1;
    }
    else if(strcmp(funct3, f3LU[2]) == 0) {
        return 2;
    }
    else if(strcmp(funct3, f3LU[3]) == 0) {
        return 3;
    }
    else if(strcmp(funct3, f3LU[4]) == 0) {
        return 4;
    }
    else if(strcmp(funct3, f3LU[5]) == 0) {
        return 5;
    }
    else if(strcmp(funct3, f3LU[6]) == 0) {
        return 6;
    }
    else if(strcmp(funct3, f3LU[7]) == 0) {
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
int parse_funct7(const char* instr){
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
int parse_immediate(const char* instr){
    char op = parse_instructions(instr);
    int val = 0;
    

    if(op == 'R') {
        return -1;                  //indicates no immediate used JLP
    }
    else if(op == 'I') {
        val = sub_parse_Imm(instr,20, instrSz);
        //printf("%i Immediate: \n", val);
        //printf("%x Imm in hex: ", val);      //for testing, should be in print
        return val;
    }
    else if(op == 'S') {
         val = sub_parse_Imm(instr, 25, instrSz) + sub_parse_Imm(instr, 7, 11);
        return val;
    }
    else if(op == 'B') {
        //consider lumping with S... JLP
    }
    else if(op == 'U') {
        //call function parse_Imm_U(instr);
        //covers U & UJ
    }
    
    return -1;              //indicates no go
}



/*
//sub_parse_Imm takes a char* & 2 ints, the instruction
//entered by the user, the start & end of the instruction
// and parses ? digits depending on 
//what instruction type it is and calculates the decimal value
//Called by: parse_immiate
//Argument: char* instr, 
//Returns: int represents the immediate decimal value
*/

int sub_parse_Imm(const char* instr, int start, int end) {    //most of the time end is instrSz
    //int im_start = 20;
    int bin_bit_value = 1;
    int imm_deci_value = 0;

    for (int i = start; i < end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[instrSz -i -1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            imm_deci_value = imm_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    //check if it is negative, if so convert
    if (imm_deci_value > 15) {
        imm_deci_value = twosComp(instr, start, end);
    }
    return imm_deci_value;
}

/************************************************************
//twoComp takes a char* & 2 ints, the instruction
//entered by the user, the start & end of the instruction
// and parses ? digits depending on the start end 
//then finds the 2's compliment and decimal value
//Called by: parse_immiate
//Argument: char* instr, int start, int end
//Returns: int represents the immediate decimal value
*///**********************************************************
int twosComp(const char* instr, int start, int end) {
    //int b = end - start;
    //printf("%d The size of ones&twos comp: \n", b);
    char onesComp[end - start];
    char twosComp[end - start];
    int carryBit = 1;
    int j = 0;

    for (int i = start; i < end; i++) {
        if(instr[instrSz - i -1] == '0'){
            onesComp[j] = '1';
        }
        else {
            onesComp[j] = '0'; 
        }
        j++;
    }
    //onesComp[end-start] = '\0';
    for (int k = end - start; k > 0; k--) {
        if(onesComp[k] == '1' && carryBit == 1) {
            twosComp[k] = '0';
        }
        else if(onesComp[k] == '0' && carryBit == 1) {
            twosComp[k] = '1';
            carryBit = 0;
        }
        else {
            twosComp[k] = onesComp[k];
        }
    }
    //twosComp[end-start] = '\0';

    printf("%s\n", twosComp);
    return 0; //will convert to a decimal next, want to see if it works so far...
}

//******************************************
//parse_register will take a char arg and then
//read the register value and return the int associated with the c-string of binary
//might want to also pass what specific register we're trying to read if passing the
//full instruction or we could in the main function break it up into registers
//based on instruction type and just have this function read them and return the proper
//int to be printed
//******************************************
void parse_register(const char* instr){
    char op = parse_instructions(instr);

    //all have register rd
    if(op == 'R' || op == 'U' || op == 'I') {
        int rd = sub_parse_reg_rd(instr);
        printf("Rd: x%i \n", rd);

        //only R and I have both RD and RS1
        if(op == 'R' || op == 'I') {
            int rs1 = sub_parse_reg_rs1(instr);
            printf("Rs1: x%i \n", rs1);

            //only R has RD, RS1 and RS2
            if(op == 'R'){
                int rs2 = sub_parse_reg_rs2(instr);
                printf("Rs2: x%i \n", rs2);
            }
        }
    }
    //only have rs 1 and rs 2
    else if(op == 'S' || op == 'B') {
        int rs1 = sub_parse_reg_rs1(instr);
        printf("Rs1: x%i \n", rs1);
        int rs2 = sub_parse_reg_rs2(instr);
        printf("Rs2: x%i \n", rs2);
    }
    else{
        printf("ERROR: INVALID INSTRUCTION INPUT \n");
    }

}


int sub_parse_reg_rd(const char* instr) {
    int rd_start = 7;
    int rd_end = 11;
    int bin_bit_value = 1;
    int rd_deci_value = 0;

    for (int i = rd_start; i < rd_end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[rd_end - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            rd_deci_value = rd_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return rd_deci_value;
}



int sub_parse_reg_rs1(const char* instr){
    int rs1_start = 15;
    int rs1_end = 19;
    int bin_bit_value = 1;
    int rs1_deci_value = 0;

    for (int i = rs1_start; i < rs1_end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[rs1_end - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            rs1_deci_value = rs1_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return rs1_deci_value;
}


int sub_parse_reg_rs2(const char* instr){
    int rs2_start = 20;
    int rs2_end = 24;
    int bin_bit_value = 1;
    int rs2_deci_value = 0;

    for (int i = rs2_start; i < rs2_end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[rs2_end - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            rs2_deci_value = rs2_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return rs2_deci_value;
}