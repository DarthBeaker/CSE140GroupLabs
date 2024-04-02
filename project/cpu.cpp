#include "cpu.hpp"


using namespace std;


Cpu::Cpu(){

}

Cpu::~Cpu(){

}

//simplistic version of Reading the register file.
//arg is the desired register; it returns the int...

int Cpu::Read_rf(int ptr) {
    
    return rf[ptr];

}

void Cpu::Decode(const char* instr) {  //this is the rf call
    char op;
    int instr, funct_3, funct_7, imme, rd, rs1, rs2;

    //will need to call Read_rf and pass to parse...
    //fetch each instruction sequentially 0 - 32
    for(int i = 0; i < 32; i++) {
        instr = Read_rf(i);
        op = parse_instructions(instr);
        funct_3 = parse_funct3;
        funct_7 = parse_funct7;
        imme = parse_immediate(instr);
        //borrowed from parse register function that chooses the registers?
        if(op == 'R' || op == 'J' || op == 'I') {
            rd = sub_parse_reg_rd(instr);

            if(op == 'R' || op == 'I'){
                
                rs1 = sub_parse_reg_rs1(instr);
                if(op == 'R'){
                    rs2 = sub_parse_reg_rs2(instr);
                    if(funct_3 == 000 && funct_7 == 0000000) {  //Alu cntl int
                        alu_ctrl = 0010;
                    }
                    else if(funct_3 == 000 && funct_7 == 0100000){
                        alu_ctrl = 0110;
                    }
                    else if(funct_3 == 111 && funct_7 == 0000000) {
                        alu_ctrl = 0000;
                    }
                    else if(funct_3 == 110 && funct_7 == 0000000) {
                        alu_ctrl = 0001;
                    }
                }
            }
        }
        else if(op == 'S' || op == 'B') {
            int rs1 = sub_parse_reg_rs1(instr);
            //printf("Rs1: x%i \n", rs1);
            int rs2 = sub_parse_reg_rs2(instr);
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
    int data = 0;

    addr = Trans_Hex(hex);

    addr = addr/4; //may move this to translate JLP
    data = d_mem[addr]; //get the data for Writeback() JLP
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
    if(opcode == 0100011) {
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
    
}
void Cpu::Execute(){

}
void Cpu::Writeback(){

}