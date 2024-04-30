#include <string>
#include <string.h>
#include "parse.hpp"



//******************************************
//parse_instructions takes a std::string arg, the instruction
//entered by the user, and parses the last 7 digits (binary)
//then recognizes its type. When the type is recognized, a
//string is returned for use  in other functions function
//Called by: parse_immediate function, print function, parse_immediate, parse_register, Decode()
//Argument: std::string instr user entered instruction
//Returns: std::string representing the OpCode (7 digits)
//******************************************

std::string parse_instructions(std::string instr){   //since the Opcode is always the last 7 bits, we can easily extract them
    
    std::string opCode = "";
    
    for(int i = instrSz - opCodeSz; i < instrSz; i++) { 
        opCode += instr[i]; 
        //printf("%i\n", i); //is iteration happening as expected? JLP
    }
    //must have null terminated character
    //opCode[opCodeSz] = '\0';

    //printf("%s\n", opCode); // is opCode correct?
    
    for(int i = 0; i < opCodeSz; i++){
        if(opCode == opCodeLU[i]) {
    //if(strcmp(opCode , opCodeLU[0].c_str()) == 0) {            //Which type is it? JLP
        
            return opCode;
        }    
    }

    printf("%s\n", "Invalid Code");         
    return "Z";                            //Note: shorthand for invalid code JLP
}

//******************************************
//parse_funct3 takes a std::string arg, the instruction
//entered by the user, and parses 3 digits (binary) 12 -14
//then recognizes the funct3 code. When the code is recognized, a
//single int is returned for intrepretation in the print function
//Called by: print function, Decode()
//Argument: std::string
//Returns: int represents the funct3 code
//******************************************

int parse_funct3(std::string instr) {
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

    //turned if/else chain into for loop
    for(int i = 0; i < numOfFunct7; i++){
        if(strcmp(funct3, f3LU[i].c_str()) == 0) {
            return i;
        }
    }

    return 8;                               //Indicates failure, should not be this big JLP
}



//******************************************
//parse_funct7 takes a std::string arg, the instruction
//entered by the user, and parses 7 digits (binary) 25-31
//then recognizes the funct3 code. When the code is recognized, a
//single int is returned for intrepretation in the print function
//Called by: print function, Decode()
//Argument: std::string
//Returns: int represents the funct7 code
//******************************************
int parse_funct7(std::string instr){
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
//parse_immediate takes a std::string arg, the instruction
//entered by the user, and parses ? digits depending on 
//what instruction type it is
//Called by: print function, Decode()
//Argument: std::string 
//Returns: int represents the immediate
*/
int parse_immediate(std::string instr){
    std::string op = parse_instructions(instr);
    int val = 0;
    int len = 0;
    std::string imme;
    //char imme[] = "000000000000";
   
    int j = 0;

    if(op == opCodeLU[4] || op == opCodeLU[5]) {
        len = 12;
        imme = "000000000000";
    }
    else {
        len = 20;
        imme = "00000000000000000000";
    }
    //char *imme = malloc(sizeof(char) * (len + 1));

    if(op == opCodeLU[0]) {         //R instruction
        return -1;                  //indicates no immediate used JLP
    }
    else if(op == opCodeLU[1] || op == opCodeLU[2] || op == opCodeLU[3]) {  //any of the 3 I instructions JLP
        val = sub_parse_Imm(instr,20, instrSz);
        return val;
    }
    else if(op == opCodeLU[4]) {        //S-type instruction (sw) JLP
         //read immedates 
        
        for(int i = 25; i < instrSz; i++) {
            imme[j] = instr[instrSz - i - 1];
            j++;
        }
        for (int i = 20; i <= 24; i++) {
            imme[j] = instr[i];
            j++;
        }
        //printf("%s\n", imme);
        val = sub_parse_Imm(imme, 0, 12);

        if(val > 2048) {
            val = twosComp(val);
            //printf("%d\n", val);
        }
        return val;
    }
    else if(op == opCodeLU[5]) {    // SB (branch) type
        j = 2;
        imme[0] = instr[0];
        imme[1] = instr[24];
        for(int i = 1; i < 7; i++) {
            imme[j] = instr[i];
            j++;
        }
        for(int k = 20; k < 24; k++){
            imme[j] = instr[k];
            j++;
        }
        val = sub_parse_Imm(imme, 0, 12);


        if(val > 2048) {
            val = twosComp(val);
        }

        return (val * 2); 
    }
   else if(op == opCodeLU[6] || op == opCodeLU[7]) { //jal or jalr 
        //call function parse_Imm_U(instr);
        //covers JAL & JALR
        int j = 0;
        imme[j] = instr[0];
        j++;
        for(int i = 12; i <= 19; i++) {
            imme[j] = instr[i];
            j++;
        }
        //j should be 12
        imme[j] = instr[11];
        j++;
        for(int k = 1; k < 11; k++){
            imme[j] = instr[k];
            j++;
        }
        //printf("j: %i, Imme: %s \n", j, imme);
        val = sub_parse_Imm(imme, 0, 20);
        
        val *= 2;


        return val;
    }
    
    return -1;              //indicates no go
}



/*
//sub_parse_Imm takes a char* & 2 ints, the instruction
//entered by the user, the start & end of the instruction
// and parses ? digits depending on 
//what instruction type it is and calculates the decimal value
//Called by: parse_immediate
//Argument: std::string instr, int start, int end 
//Returns: int represents the immediate decimal value
*/

int sub_parse_Imm(std::string instr, int start, int end ) {    //most of the time end is instrSz
    //int im_start = 20; fall back to check for S error JLP
    int bin_bit_value = 1;
    int imm_deci_value = 0;

    for (int i = start; i < end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[end - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            imm_deci_value = imm_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return imm_deci_value;
}


/************************************************************
//twoComp takes an int argument the immediate value from the
// instruction; converts it from decimal to binary, flips the 
//bits then finds the 2's compliment and decimal value
//Called by: parse_immiate
//Argument: char* instr, int start, int end
//Returns: int represents the immediate decimal value
*///**********************************************************
int twosComp(int num) {
    int value = 0;
    char onesComp[] = "000000000000";
    char twosComp[] = "000000000000";
    int carryBit = 1;
    int j = 0;
    int dec = num; 
    int rem = 0;
    char bin[] = "000000000000";
    int imm_deci_value = 0;
    int bin_bit_value = 1;
    //convert the decimal to binary
    for(int i = 11; dec != 0; i--) {
        rem = dec % 2; 
        dec /= 2;
        if(rem == 0){
            bin[i] = '0';
        }
        else {
            bin[i] = '1';
        }
    }
    //flip bits
    for (int i = 0; i < 12; i++) {
        if(bin[i] == '0'){
            onesComp[j] = '1';
        }
        else {
            onesComp[j] = '0'; 
        }
        j++;
    }
    
    for (int k = 11; k >= 0; k--) {
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
    //printf("%s", "Twos Comp: ");
    //  printf("%s\n", twosComp);

    for(int i = 0; i < 12; i++) {
         if(twosComp[12 - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else{
            imm_deci_value = imm_deci_value + bin_bit_value; 
            bin_bit_value = bin_bit_value * 2; 
        }
    }

    return -imm_deci_value;
}


//******************************************
//parse_register will take a std::string arg and then
//read the register value and return the int associated with the c-string of binary
//might want to also pass what specific register we're trying to read if passing the
//full instruction or we could in the main function break it up into registers
//based on instruction type and just have this function read them and return the proper
//int to be printed
//******************************************
void parse_register(std::string instr){
    std::string op = parse_instructions(instr);

    //all have register rd
    if(op == opCodeLU[0] || op == opCodeLU[6] || op == opCodeLU[1] || op == opCodeLU[2] || op == opCodeLU[3]) {
        int rd = sub_parse_reg_rd(instr);

        //only R and I have both RD and RS1
        if(op == opCodeLU[0] || op == opCodeLU[1] || op == opCodeLU[2] || op == opCodeLU[3]) {
            int rs1 = sub_parse_reg_rs1(instr);
            printf("Rs1: x%i \n", rs1);

            //only R has RD, RS1 and RS2
            if(op == opCodeLU[0]){
                int rs2 = sub_parse_reg_rs2(instr);
                printf("Rs2: x%i \n", rs2);
            }
        }

        printf("Rd: x%i \n", rd);
    }
    //only have rs 1 and rs 2
    else if(op == opCodeLU[4] || op == opCodeLU[5]){
        int rs1 = sub_parse_reg_rs1(instr);
        printf("Rs1: x%i \n", rs1);
        int rs2 = sub_parse_reg_rs2(instr);
        printf("Rs2: x%i \n", rs2);
    }
    else{
        printf("ERROR: INVALID INSTRUCTION INPUT \n");
    }

}

//****************************************************
//sub_parse_reg_rd will take a std::string arg and then
//extract the value of the destination register from the instruction
//converts it to a decimal value and returns it.
//Called by: parse_register, Decode()
//Agurment: std::string representing an instruction
//Returns: an integer representing the decimal value of the destination register
//****************************************************

int sub_parse_reg_rd(std::string instr) {
    int rd_start = 7;
    int rd_end = 11;
    int bin_bit_value = 1;
    int rd_deci_value = 0;

    for (int i = rd_start; i <= rd_end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[instrSz - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            rd_deci_value = rd_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return rd_deci_value;
}

//****************************************************
//sub_parse_reg_rs1 will take a std::string arg and then
//extract the value of the Rs1 register from the instruction
//converts it to a decimal value and returns it.
//Called by: parse_register, Decode()
//Agurment: std::string representing an instruction
//Returns: an integer representing the decimal value of the Rs1 register
//****************************************************

int sub_parse_reg_rs1(std::string instr) {
    int rs1_start = 15;
    int rs1_end = 19;
    int bin_bit_value = 1;
    int rs1_deci_value = 0;

    for (int i = rs1_start; i <= rs1_end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[instrSz - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            rs1_deci_value = rs1_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return rs1_deci_value;
}

//****************************************************
//sub_parse_reg_rs2 will take a std::string arg and then
//extract the value of the destination register from the instruction
//converts it to a decimal value and returns it.
//Called by: parse_register, Decode()
//Agurment: std::string representing an instruction
//Returns: an integer representing the decimal value of the Rs2 register
//****************************************************
int sub_parse_reg_rs2(std::string instr){
    int rs2_start = 20;
    int rs2_end = 24;
    int bin_bit_value = 1;
    int rs2_deci_value = 0;

    for (int i = rs2_start; i <= rs2_end; i++) { //want the decimal & hex values
        //calculate the binary
        if(instr[instrSz - i - 1] == '0') {
            bin_bit_value = bin_bit_value * 2;
        }
        else {
            rs2_deci_value = rs2_deci_value + bin_bit_value;
            bin_bit_value = bin_bit_value * 2;
        }
    }
    return rs2_deci_value;
}


