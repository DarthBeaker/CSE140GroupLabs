#include "cpu.hpp"


using namespace std;


Cpu::Cpu(){

}

Cpu::~Cpu(){

}

Cpu::Decode(const char* instr) {  //this is the rf call
    char letter;
    int funct_3, funct_7, imme, rd, rs1, rs2;

    letter = parse_instructions(instr);
    funct_3 = parse_funct3;
    funct_7 = parse_funct7;
    imme = parse_immediate(instr);
    //new parse register function that chooses the registers?
    rd = sub_parse_reg_rd(instr);
    rs1 = sub_parse_reg_rs1(instr);
    rs2 = sub_parse_reg_rs2(instr);


}