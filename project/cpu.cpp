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

Cpu::Decode(const char* instr) {  //this is the rf call
    char op;
    int funct_3, funct_7, imme, rd, rs1, rs2;
    //will need to call Read_rf and pass to parse...

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
            }
        }
    }
    else if(op == 'S' || op == 'B') {
        int rs1 = sub_parse_reg_rs1(instr);
        //printf("Rs1: x%i \n", rs1);
        int rs2 = sub_parse_reg_rs2(instr);
        //printf("Rs2: x%i \n", rs2);
    }

    //rd = sub_parse_reg_rd(instr);
    //rs1 = sub_parse_reg_rs1(instr);
    //rs2 = sub_parse_reg_rs2(instr);


}