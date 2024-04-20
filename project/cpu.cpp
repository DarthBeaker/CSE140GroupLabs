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
    read_data_1 = rf[sub_parse_reg_rs1(instruction_fetched)];
    read_data_2 = rf[sub_parse_reg_rs2(instruction_fetched)];

    if(op == 'R' || op == 'J' || op == 'I') {
        dest_reg = sub_parse_reg_rd(instruction_fetched);

        if(op == 'R' || op == 'I') {
                
            if(op == 'I') {
                read_data_2 = imme;

                if(op == 'I' && funct_3 == 010) {  //if lw instr send opcode
                    ControlUnit(00000011); // 
                } 
                else if(op = 'I' && (funct_3 == 000 || funct_3 == 110 || funct_3 == 111)) { //may not need the funct_3 check... need to look at I instru list
                    ControlUnit(0010011);
                }
            }
                
            else if(op == 'R') {    //pass the R opcode to Control_Unit here JLP
                ControlUnit(0110011);        //something like this JLP

                //Remove when sure code is functional JLP 
                // if(funct_3 == 000 && funct_7 == 0000000) {  //Alu cntl int move this to Control_unit JLP
                //     alu_ctrl = "0010";
                // }
                // else if(funct_3 == 000 && funct_7 == 0100000){  //move to Control_Unit JLP
                //     alu_ctrl = "0110";
                // }
                // else if(funct_3 == 111 && funct_7 == 0000000) { //move to Control_Unit JLP
                //     alu_ctrl = "0000";
                // }
                // else if(funct_3 == 110 && funct_7 == 0000000) { //move to Control_Unit JLP
                //     alu_ctrl = "0001";
                // }
            }
        }
    }
    else if(op == 'S' || op == 'B') {   //here will need to add opcode passing to Control_Unit JLP

        if(op == 'S' && funct_3 == 010) {       //move to Control Unit JLP
            alu_ctrl = "0010";
        }
        else if(op == 'B' && funct_3 == 000) {  //move to Control Unit JLP
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
    //ALU calculates target memory address in Exe().
    //addr = Trans_Hex(hex); probably do not need.
    //addr = addr/4; probably do not need
    
    if(mem_read == true && mem_write == false) {
        //need address to read from; from Exe() for LW
       rf[dest_reg] = d_mem[branch_target] //sent to WriteBack()

    }

    if(mem_write == true && mem_read == false) {
        //need address to write to from Exe()
        //need data = rf[addr] I think JLP
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
        if(funct_3 == 000 && funct_7 == 0000000) {  // add instr JLP
                    alu_ctrl = "0010";
                }
                else if(funct_3 == 000 && funct_7 == 0100000){  // sub instr JLP
                    alu_ctrl = "0110";
                }
                else if(funct_3 == 111 && funct_7 == 0000000) { //and instr JLP
                    alu_ctrl = "0000";
                }
                else if(funct_3 == 110 && funct_7 == 0000000) { //or instr JLP
                    alu_ctrl = "0001";
                }
    }
    
    //if lw JLP
    else if(opcode == 0000011) {
        reg_write = true; 
        alu_src = true;
        mem_to_reg = true; 
        mem_read = true;
        alu_op = 00;
        alu_ctrl = "0010";
    } //JLP
    //I type not lw
    else if (opcode == 0010011) { //andi, ori, addi
        if(funct_3 == 000) { //addi
            //alu_ctrl = "0010"; 
        }
        else if(funct_3 == 110) { //ori
            //alu_ctrl = "ori";
        }
        else if(funct_3 == 111) { //andi
            //alu_ctrl = "andi";
        }
        //alu_op = 10; // think it is the same for all 3...
        //if(funct_3 == 000) {          //addi
            //reg_read = true;
            //alu_src = true;
            //reg_write = true;
        //}
        //else if(funct_3 == 111) {     //lndi
            
        //}
        //else if(funct_3 == 110) {        //ori
            //?
        //}
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