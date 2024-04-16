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
    int funct_3, funct_7, imme,;

    //will need to call Read_rf and pass to parse...

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
    //ALU calculates target memory address in Exe()?
    addr = Trans_Hex(hex);
    addr = addr/4;
    
    if(mem_read == true && mem_write == false) {
        //need address to read from; from Exe() for LW
        //d_mem[addr] sent to WriteBack()

    }

    if(mem_write == true && mem_read == false) {
        //need address to write to from Exe()
        //need data from which register?
        //SW, needs d_mem[addr] = data
    }

    addr = addr/4; //may move this to translate JLP
    read_d_mem = d_mem[addr]; //get the data for Writeback() JLP
    //do some variables for lw/sw need updating here? JLP

}

void Cpu::ControlUnit(int opcode) {     //opcode is 7-bits
// set all control signals to false when we start...JLP
    reg_write = false;
    alu_op = 11; // none of the ones we need us this one, so is effectively zero JLP
    alu_src = false;
    mem_to_reg = false;
    mem_read = false;
    mem_write = false;
    branch = false;
    

    //if R-type
    if(opcode == 0110011) {
        reg_write = true;
        alu_op = 10;
    }
    
    //if lw JLP
    else if(opcode == 0000011) {
        reg_write = true; 
        alu_src = true;
        mem_to_reg = true; 
        mem_read = true;
        alu_op = 00;
    } //JLP
    //I type not lw
    else if (opcode == 0010011) {
        //not sure if we need JLP
    }
   
    //S-type, sw JLP
    if(opcode == 0100011) { //if store word, same as lw, with mem_write true JLP
        alu_op = 00;
        reg_write = true;
        mem_read = true;
        mem_to_reg = true;
        mem_write = true;
        alu_src = true;         //for Mux 0 or 1

    }

    //if SB JLP
    if(opcode == 1100011) {
        branch = true;
        alu_op = 01;
    }


    ///*
        //if JALR 1100111 is an I instruction...
        if(opcode == 1100111) {
            //mem_to_reg = true; 
            //mem_read = true; 
            //reg_write = true;
            //alu_op = 00; //set to add
            //branch = true; 
            //alu_src = true;
            //reg_write = true; //writing the return address back
            
        }
         //JAL 1101111
         if(opcode == 1101111) {
            //alu_op == 00; //set to add
            //branch = true;
            //mem_read = true;
            //reg_write = true; 
            //alu_src = true;

         }
    //*/

   
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
    //AND
    if(alu_ctrl == "0000"){
        alu_output = read_data_1 & read_data_2;
    }
    //OR
    else if(alu_ctrl == "0001"){
        alu_output = read_data_1 | read_data_2;
    }
    //ADD
    else if(alu_ctrl == "0010"){
        alu_output = read_data_1 + read_data_2;
    }
    //SUB
    else if(alu_ctrl == "0110"){
        alu_output = read_data_1 - read_data_2;
    }

    if(branch){
        branch_target = next_pc + (read_imme << 1);
        if(alu_output == 0){
            alu_zero == true;
        }
    }
}


void Cpu::Writeback(){

    //if writing to memory we don't need to write back
    if(reg_write){
        if(mem_to_reg){
            //read data read in Mem() by LW
            rf[dest_reg] = read_d_mem;
        }
        else{
            //read data from ALU_output and store in register
            rf[dest_reg] = alu_output;
        }
    }

    //Cycle complete increment total clock cycles
    total_clock_cycles++;
}