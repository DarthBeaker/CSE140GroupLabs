#ifndef PARSE_H
#define PARSE_H

#include <string>

//define the field sizes to avoid magic numbers JLP
const int instrSz = 32;    
const int opCodeSz = 7; 
const int funct3Sz = 3;
const int funct7Sz = 7;
const int rdSz = 5; 
const int rsSz = 5; 
const int ImmI = 5; 
const int ImmSz2 = 16; 
const int numOfFunct7 = 8;
//opcode look-up table     R-instr    I-instr    I-instr    I-instr    S-instr   SB-instr     UJ-instr   
std::string opCodeLU[] = {"0110011", "0010011", "0000011", "1100111", "0100011", "1100011", "1101111"};
std::string f3LU[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
//function definitions
void print_instructions(std::string); //main function will call subfunctions KP
std::string parse_instructions(std::string); //find the opcode, returns instruct type KP
int parse_funct3(std::string);
int parse_funct7(std::string);
int parse_immediate(std::string);
void parse_register(std::string);
int sub_parse_Imm(std::string, int, int);
int twosComp(int);
int sub_parse_reg_rd(std::string instr);
int sub_parse_reg_rs1(std::string instr);
int sub_parse_reg_rs2(std::string instr);
int sub_parse_Imm_S(std::string);



#endif