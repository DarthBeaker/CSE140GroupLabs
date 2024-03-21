#ifndef CPU_H
#define CPU_H

#include <string>
#include "parse.c"

class Cpu{
private:
<<<<<<< HEAD
    char rf[32] = {'00000000000000000000000000000000'};
=======
    //As Defined by the documetion required
    int rf[32] = {0};
>>>>>>> 5b063a38320f1f036f4fe2155b66852d89b80490
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

<<<<<<< HEAD
    Decode(const char* );

=======
    void Fetch(std::string filename_input);
    void Decode();
    void Execute();
    void Mem();
    void Writeback();
>>>>>>> 5b063a38320f1f036f4fe2155b66852d89b80490

};


#endif