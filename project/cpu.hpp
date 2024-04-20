#ifndef CPU_H
#define CPU_H

#include <string>
#include "parse.c"
#include "parse.cpp"

class Cpu{
private:
    int rf[32] = {0};
    int d_mem[32] = {0};
    int pc;
    int next_pc;
    std::string alu_ctrl;
    bool alu_zero; //could also be int technically
    int branch_target;
    int total_clock_cycles;
    bool reg_write;
    bool branch;
    bool alu_src;
    bool mem_read;
    bool mem_to_reg;
    bool mem_write;
    int alu_op; //JLP needed by control unit, may need to be a string or char
    int funct_3;
    int funct_7; 

    //Our own Varible that we decide we need
    std::string intruction_fetched;
    std::string filename;


    //required by the class
    void ControlUnit(int opcode);
    std::string Alu_Ctrl(int funct_3, int funct_7, int alu_op);
    
    //our own functions
    int Trans_Hex(std::string hex);
    int Read_rf(int ptr);

    //for storing between the stages
    int read_data_1;
    int read_data_2;
    int read_imme; //specifically for S and SB types used to pass between decode and exec
    int alu_output;
    int read_d_mem;
    int dest_reg;


public:
    Cpu();
    ~Cpu();


    void Decode(std::string instr);
    void Fetch(std::string filename_input);
    void Decode();
    void Execute();
    void Mem();
    void Writeback();

};


#endif