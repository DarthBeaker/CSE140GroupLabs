#include <stdio.h>               
#include <string.h>  
//define the field sizes to avoid magic numbers JLP
const int instrSz = 32;    
const int opCodeSz = 7; 
const int funct3Sz = 3;
const int funct7Sz = 7;
const int rdSz = 5; 
const int rsSz = 5; 
const int ImmI = 5; 
const int ImmSz2 = 16; 
//opcode look-up table     R-instr    I-instr    I-instr    I-instr    S-instr   SB-instr     UJ-instr   
const char* opCodeLU[] = {"0110011", "0010011", "0000011", "1100111", "0100011", "1100011", "1101111"};
const char* f3LU[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
//function definitions
void print_instructions(const char*); //main function will call subfunctions KP
char parse_instructions(const char*); //find the opcode, returns instruct type KP
int parse_funct3(const char*);
int parse_funct7(const char*);
int parse_immediate(const char*);
void parse_register(const char*);
int sub_parse_Imm(const char*, int, int);
int twosComp(int);
int sub_parse_reg_rd(const char* instr);
int sub_parse_reg_rs1(const char* instr);
int sub_parse_reg_rs2(const char* instr);
int sub_parse_Imm_S(const char*);



 



void main() {
                            //Gets the instruction from the user JLP
    char instr[instrSz + 1];
    
    printf("Enter an instruction: ");

    fgets(instr, instrSz + 1, stdin);

    print_instructions(instr);

    
}

























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
//parse_immediate takes a const char* arg, the instruction
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
        return val;
    }
    else if(op == 'S') {
        //read immedates 
        char imme[] = "000000000000";
        int j = 0;
        for(int i = 25; i < instrSz; i++) {
            imme[j] = instr[instrSz - i - 1];
            j++;
        }
        for (int i = 20; i <= 24; i++) {
            imme[j] = instr[i];
            j++;
        }
        printf("%s\n", imme);
        val = sub_parse_Imm(imme, 0, 12);
        //printf("%d\n", val);

        if(val > 2048) {
            val = twosComp(val);
            //printf("%d\n", val);
        }
        return val;
    }
    else if(op == 'B') {
        int j = 2;
        char imme[] = "000000000000";
        imme[0] = instr[31];
        imme[1] = instr[7];
        for(int i = 25; i < 30; i++) {
            imme[j] = instr[30 - i - 1];
            j++;
        }
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

int sub_parse_Imm(const char* instr, int start, int end ) {    //most of the time end is instrSz
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
//twoComp takes a char* & 2 ints, the instruction
//entered by the user, the start & end of the instruction
// and parses ? digits depending on the start end 
//then finds the 2's compliment and decimal value
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
    printf("%s", "Twos Comp: ");
    printf("%s\n", twosComp);

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
    if(op == 'R' || op == 'J' || op == 'I') {
        int rd = sub_parse_reg_rd(instr);

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

        printf("Rd: x%i \n", rd);
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



int sub_parse_reg_rs1(const char* instr){
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


int sub_parse_reg_rs2(const char* instr){
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

/******************************************
//print_instructions will take 1 arg  and return nothing
//Its sole job is to print all the fields correctly.
//might want to also pass what specific register we're trying to read if passing the
//full instruction or we could in the main function break it up into registers
//based on instruction type and just have this function read them and return the proper
//int to be printed

//R Type
add sub -- done
sll slt sltu -- done
xor --done
sra srl --done
or and  --done

//I Type
lb lh lw --done
addi slli slti sltiu xori srli srai ori andi
jalr 



//S Type
sb sh sw --done

//SB Type
beq bge blt bne

//UJ Type
jal -- done
/****************************************/
void print_instructions(const char* instr){
    char instr_type = parse_instructions(instr);
    int funct3 = parse_funct3(instr);
    int funct7 = parse_funct7(instr);
    //for the instructions given only I has different opcodes
    //so I must get the opcode so I can search through each one for the right codes
    int op_start = 0;
    int op_end = 7;
    int bin_bit_value = 1;
    int opcode = 0;
    for (int i = op_start; i < op_end; i++) {
        if(instr[instrSz - i - 1] == '0') {
            bin_bit_value *= 2;
        }
        else {
            opcode += bin_bit_value;
            bin_bit_value *= 2;
        }
    }

    printf("%s", "Instruction Type: ");
    if(instr_type != 'B' && instr_type != 'J'){
        printf("%c\n", instr_type);
    }
    else if(instr_type == 'J'){
        printf("UJ\n");
    }
    else{
        printf("SB\n"); //instruction type stored as char we shortened SB -> B internally and we can't just print B so we must print SB instead
    }
    printf("%s", "Operation: ");

    switch(instr_type){
        case 'R':
            switch(funct3){
                case 0:
                    //funct7 is only 0 or 32 I believe
                    if(funct7 == 0){
                        printf("add \n");
                    }
                    else{
                        printf("sub \n");
                    }
                    break;
                case 1:
                    printf("sll \n");
                    break;
                case 2:
                    printf("slt \n");
                    break;
                case 3:
                    printf("sltu \n");
                    break;
                case 4:
                    printf("xor \n");
                    break;
                case 5:
                    //funct7 is only 0 or 32 I believe
                    if(funct7 == 0){
                        printf("srl \n");
                    }
                    else{
                        printf("sra \n");
                    }
                    break;
                case 6:
                    printf("or \n");
                    break;
                case 7:
                    printf("and \n");
                    break;  
            }
            break;
        case 'I':
            //printf("opcode: %i", opcode);
            switch(opcode){
                case 3:
                    switch(funct3){
                        case 0:
                            printf("lb \n");
                            break;
                        case 1:
                            printf("lh \n");
                            break;
                        case 2:
                            printf("lw \n");
                            break;
                    }
                    break;
                case 19:
                    switch(funct3){
                        case 0:
                            printf("addi \n");
                            break;
                        case 1:
                            printf("slli \n");
                            break;
                        case 2:
                            printf("slti \n");
                            break;
                        case 3:
                            printf("sltiu \n");
                            break;
                        case 4:
                            printf("xori \n");
                            break;
                        case 5:
                            if(funct7 == 0){
                                printf("srli \n");
                            }
                            else{
                                printf("srai \n");
                            }
                            break;
                        case 6:
                            printf("ori \n");
                            break;
                        case 7:
                            printf("andi \n");
                            break;
                    }
                    break;
                case 103:
                    // can only be jalr
                    printf("jalr \n");
                    break;
            }
            break;
        case 'S':
            switch(funct3){
                case 0:
                    printf("sb \n");
                    break;
                case 1:
                    printf("sh \n");
                    break;
                case 2:
                    printf("sw \n");
                    break;
            }
            break;
        case 'B':
            switch(funct3){
                case 0:
                    printf("beq \n");
                    break;
                case 1:
                    printf("bne \n");
                    break;
                case 4:
                    printf("blt \n");
                    break;
                case 5:
                    printf("bge \n");
                    break;
            }
            break;
        case 'J': //only 1 UJ statment so just print what it is
            printf("jal \n");
            break;
        default:
            printf("ERROR: INVALID INSTRUCTION \n");
    }
    parse_register(instr);
    //call parse_funct3 and print the decimal value of it for now.
    if(instr_type != 'J'){
        printf("Funct3: %i\n", funct3);
    }
    
    if(instr_type == 'R'){
        printf("Funct7: %i\n", funct7);
    }
    else{
        printf("Immediate: %i\n", parse_immediate(instr));
    }
}