#ifndef CPU_H
#define CPU_H

#include <string>

class Cpu{
private:
    // //for sample_part1: x1 = 0x20, x2 = 0x5, x10 = 0x70, x11 = 0x4
    // int rf[32] = {
    //     0, 0x20, 0x5, 0, 
    //     0, 0, 0, 0, 
    //     0, 0, 0x70, 0x4,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0
    //     };
    // //for sample_part1: 0x70 = 0x5, 0x74 = 0x10 (remember each entry count by 4)
    // int d_mem[32] = {
    //     0, 0, 0, 0, 
    //     0, 0, 0, 0, 
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0x5, 0x10, 0, 0
    //     };
    //for sample_part2: s0 = 0x20, a0 = 0x5, a1 = 0x2, a2 = 0xa, a3 = 0xf
    int rf[32] = {
        0, 0, 0, 0, 
        0, 0, 0, 0, 
        0x20, 0, 0x5, 0x2,
        0xa, 0xf, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
        };
    //for sample_part2: Initialize d_mem array to all zero’s
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
    std::string instruction_fetched;
    std::string filename;


    //required by the class
    void ControlUnit(std::string opcode);
    std::string Alu_Ctrl(int funct_3, int funct_7, int alu_op);
    
    //our own functions
    int Trans_Hex(std::string hex);
    int Read_rf(int ptr);

    //for storing between the stages
    int read_data_1;
    int read_data_2;
    int read_data_s; //specifically for S types used to pass between decode and exec
    int read_imme; //specifically for SB types used to pass between decode and exec
    int alu_output;
    int read_d_mem;
    int dest_reg;

    //for running the loop
    bool if_more_instr;

    //for jalr & jal
    bool jump;
    int jump_target;

public:
    Cpu();
    ~Cpu();

    void Fetch(std::string filename_input);
    void Decode();
    void Execute();
    void Mem();
    void Writeback();
    int getTotalCycles() const {return total_clock_cycles;};
    int getPC() const {return pc;};
    bool IfMoreInstr() const {return if_more_instr;};
};


#endif