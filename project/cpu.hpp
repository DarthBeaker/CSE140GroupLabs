#ifndef CPU_H
#define CPU_H

#include <string>
#include "parse.c"

class Cpu{
private:
    char rf[32] = {'00000000000000000000000000000000'};
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

    //Our own Varible that we decide we need
    std::string intruction_fetched;
    std::string filename;


    //required by the class
    void ControlUnit(std::string opcode);

public:
    Cpu();
    ~Cpu();


    void Decode(const char* );
    void Fetch(std::string filename_input);
    void Decode();
    void Execute();
    void Mem();
    void Writeback();

};


#endif