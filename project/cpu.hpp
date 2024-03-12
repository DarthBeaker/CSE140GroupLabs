#ifndef CPU_H
#define CPU_H

#include <string>

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

    

public:
    Cpu();
    ~Cpu();


};


#endif