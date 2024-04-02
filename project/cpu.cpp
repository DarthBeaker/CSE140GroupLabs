#include <fstream>
#include "cpu.hpp"


using namespace std;


Cpu::Cpu(){
    pc = 0;
    total_clock_cycles = 0;
}

Cpu::~Cpu(){

}

//simplistic version of Reading the register file.
//arg is the desired register; it returns the int...

int Cpu::Read_rf(int ptr) {
    
    return rf[ptr];

}

void Cpu::Decode() {  //this is the rf call
    char op;
    int funct_3, funct_7, imme;

    //will need to call Read_rf and pass to parse...
    //fetch each instruction sequentially 0 - 32
    for(int i = 0; i < 32; i++) {
        instr = Read_rf(i);
        op = parse_instructions(instruction_fetched);
        funct_3 = parse_funct3(instruction_fetched);
        funct_7 = parse_funct7(instruction_fetched);
        imme = parse_immediate(instruction_fetched);
        //borrowed from parse register function that chooses the registers?
        read_data_1 = sub_parse_reg_rs1(instruction_fetched);
        read_data_2 = sub_parse_reg_rs2(instruction_fetched);

        if(op == 'R' || op == 'J' || op == 'I') {
            dest_reg = sub_parse_reg_rd(instruction_fetched);

            if(op == 'R' || op == 'I') {
                
                if(op == 'I') {
                    read_data_2 = imme;

                    if((op == 'I' && funct_3 == 010)|| (op = 'I' && funct_3 == 000)) { //lw instru && addi instru
                    
                    alu_ctrl = "0010";
                    
                    }
                }
                
                else if(op == 'R') {

                    if(funct_3 == 000 && funct_7 == 0000000) {  //Alu cntl int
                        alu_ctrl = "0010";
                    }
                    else if(funct_3 == 000 && funct_7 == 0100000){
                        alu_ctrl = "0110";
                    }
                    else if(funct_3 == 111 && funct_7 == 0000000) {
                        alu_ctrl = "0000";
                    }
                    else if(funct_3 == 110 && funct_7 == 0000000) {
                        alu_ctrl = "0001";
                    }
                }
            }
        }
        else if(op == 'S' || op == 'B') {

            if(op == 'S' && funct_3 == 010) {
                alu_ctrl = "0010";
            }
            else if(op == 'B' && funct_3 == 000) {
                alu_ctrl = "0110";
            }
        //printf("Rs2: x%i \n", rs2);
        }
    }
    //rd = sub_parse_reg_rd(instr);
    //rs1 = sub_parse_reg_rs1(instr);
    //rs2 = sub_parse_reg_rs2(instr);


}
//arg is a 8-bit memory address? No bigger?
//using a string, since hex is 0 - F
// can adjust JLP
int Cpu::Trans_Hex(std::string hex) {
    int sum = 0;
    for(int i = 0; i < 8; i++) {
        if(isdigit(hex[i])) {
            if(hex[i] == 'A') {
                sum += 11;
            }
            else if(hex[i] == 'B'){
                sum += 12;
            }
            else if(hex[i] == 'C'){
                sum += 13;
            }
            else if(hex[i] == 'D'){
                sum += 14;
            }
            else if(hex[i] == 'E'){
                sum += 15;
            }
            else if(hex[i] == 'F') {
                sum += 16;
            }
        }
        else {
            sum += hex[i];
        }
    }

    return sum; //could do sum/4, can also be done where returned JLP
}

void Cpu::Mem() {
    //need a function that will take the hex memroy address
    //and translate it into the array index we want
    int addr = 0;
    addr = Trans_Hex(hex);
    addr = addr/4;
    
    if(mem_read == true){
        //need address to read from; from Exe()

    }

    if(mem_write == true) {
        //need address to write to from Exe()
        //need data from which register?
    }

    addr = addr/4; //may move this to translate JLP
    read_d_mem = d_mem[addr]; //get the data for Writeback() JLP
    //do some variables for lw/sw need updating here? JLP

}

void Cpu::ControlUnit(int opcode) {     //opcode is 7-bits
// this is a test JLP
        
    //if R-type
    if(opcode == 0110011){
        reg_write = true;
        alu_ctrl = true;
    }
    
    //if I type or lw... may not need second JLP
    if(opcode == 0000011 || opcode == 0010011) {
        reg_write = true;
        alu_src = true;
        mem_to_reg = true;
        mem_read = true;
        alu_ctrl = true;
    } //JLP
   
    //S-type? JLP
    if(opcode == 0100011) { //if store word
        //do stuff? JLP
    }

    //if SB JLP
    if(opcode == 1100011) {
        branch = true;
        alu_ctrl = true;
    }


    /*
        if JAL or J...
    */

   // What or when does these get reset?
   // During the next instruction cycle I imagine
   
}



void Cpu::Fetch(std::string filename_input){

    //Updating PC Value
    if(!branch || !alu_zero){//if not branch
        pc = next_pc;
    }
    // This will be where we also check for jal/jalr
    // else if(){
    //    
    // }
    else{
        pc = branch_target;
    }

    //Fetching Instruction
    ifstream instruction_file;
    instruction_file.open(filename_input);

    if(instruction_file.is_open()){
        //file_position should generate the right line based in the file based off the amount of 
        //characters on a line and the current pc counter divided by 4 (since it increments by 4 each time 
        // unless branching but regardless it's multiples of four)
        // double check this actually works, at the least it should be close
        int file_position = pc/4 * 33; //each line is 33 characters (32 "bits" and then a \n)
        instruction_file.seekg(0, file_position);

        //pull instruction
        getline(instruction_file, intruction_fetched);
    }


    instruction_file.close();

    //After fetching instruction
    next_pc = pc + 4;
}

void Cpu::Execute(){
    //we made ALU_src a private string 
}


void Cpu::Writeback(){

    if(mem_to_reg){
        //read data read in Mem() by LW
        
    }
    else{
        //read data from ALU_output and store in register
    }


    //Cycle complete increment total clock cycles
    total_clock_cycles++;
}