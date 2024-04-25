#include <fstream>
#include <iostream>
#include "cpu.hpp"
#include "parse.cpp"

using namespace std;


Cpu::Cpu(){
    pc = 0x0;
    total_clock_cycles = 0;
    next_pc = pc + 4;
    if_more_instr = true;
}

Cpu::~Cpu(){

}

//simplistic version of Reading the register file.
//arg is the desired register; it returns the int...

int Cpu::Read_rf(int ptr) {
    
    return rf[ptr];

}

void Cpu::Decode() {  //this is the rf call
    string op;
    int imme;

    op = parse_instructions(instruction_fetched);
    funct_3 = parse_funct3(instruction_fetched);
    funct_7 = parse_funct7(instruction_fetched);
    imme = parse_immediate(instruction_fetched);
    //cout << "funct_3: " << funct_3 << " funct_7: " << funct_7 << "\n";
    //borrowed from parse register function that chooses the registers?
    read_data_1 = rf[sub_parse_reg_rs1(instruction_fetched)];
    read_data_2 = rf[sub_parse_reg_rs2(instruction_fetched)];
    ControlUnit(op); // all instructions regardless of its code go to controlunit JLP

    if(op == "0110011" || op == "1100111" /* jalr */ || op == "1101111" /*jal*/ || op == "0000011" || op == "0010011") {
        dest_reg = sub_parse_reg_rd(instruction_fetched); //I think this is all JAL needs JLP
        //if(op == "1101111"){
            // should work JLP
        //}
        else if(op == "1100111") {
            
            //PC = R[s1] + imme we need to do this
            //PC = rf[sub_parse_reg_rs1(instruction_fetched)] + imme
        }

        if(op == "0110011" || op == "0000011" || op == "0010011") {
                
            if(op == "0000011" || op == "0010011") {
                read_data_2 = imme;

                //Think we can safely remove this
                // if(op == "0000011" && funct_3 == 0b010) {  //if lw instr send opcode 
                //     ControlUnit(00000011); // 
                // } 
                // else { // if it is not lw, and it is I, it must have this opcode JLP
                //     ControlUnit(0010011);
                // }
            }
             //Don't think we need this either JLP   
            // else if(op == "0110011") {    //pass the R opcode to Control_Unit here JLP
            //     ControlUnit(0110011);        //something like this JLP
            // }
        }
    }
    else if(op == "0100011" ) {   //S opcode, but really just checking for sw 
        read_data_2 = imme;
        read_data_s = rf[sub_parse_reg_rs2(instruction_fetched)];
        //ControlUnit(0100011);
    }
    else if(op == "1100011") {   //SB opcode, but really just checkign for beq JLP
        read_imme = imme;
        //ControlUnit(1100011);
    //printf("Rs2: x%i \n", rs2);
    }
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

    if(mem_read || mem_write){
        addr = alu_output/4;
        if(mem_read == true && mem_write == false) {
            read_d_mem = d_mem[addr]; //get the data for Writeback() JLP
        }
        else if(mem_write == true && mem_read == false) {
            d_mem[addr] = read_data_s;
        }
    }
}

std::string Cpu::Alu_Ctrl(int f3, int f7, int aluop) {       //header file has more details about function JLP
    if(aluop == 0b00) {  //lw | sw I-type, S-type JLP
        return "0010";
    }
    else if(aluop == 10 && f7 == 0b0100000) { //R-type subtract, only one that uses f7
        return "0110";
    }
    //I-type & R-type add/addi, and/andi, or/ori
    else if(aluop == 11 || aluop == 10) {
        if(f3 == 0b000) {     //add|addi
            return "0010";
        }
        else if(f3 == 0b111) { //and|andi instr JLP
            return "0000";
        }
        else if(f3 == 0b110) {
            return "0001";
        }
    }
    // SB-type JLP
    else if(aluop == 01) {
        if(f3 == 0b000) {         //beq, will need f3 differentiation if we want to expand JLP
            return "0110";
        }
    }
} 

void Cpu::ControlUnit(std::string opcode) {     //opcode is 7-bits
// set all control signals to false when we start...JLP
    reg_write = false;
    alu_op = 22; // none of the ones we need us this one, so is effectively zero JLP
    alu_src = false;
    mem_to_reg = false;
    mem_read = false;
    mem_write = false;
    branch = false;
    

    //if R-type JLP
    if(opcode == "0110011") {
        reg_write = true;
        alu_op = 10;
        alu_ctrl = Alu_Ctrl(funct_3, funct_7, alu_op);
    } 
    
    //if lw; I-type JLP
    else if(opcode == "0000011") {
        //reg_write = true; 
        alu_src = true;
        mem_to_reg = true; 
        mem_read = true;
        alu_op = 00;
        alu_ctrl = Alu_Ctrl(funct_3, funct_7, alu_op);
    } //JLP

    //I type not lw
    else if (opcode == "0010011") { //andi, ori, addi JLP
        alu_src = true;
        reg_write = true;
        alu_op = 11;

        alu_ctrl = Alu_Ctrl(funct_3, funct_7, alu_op);
    }
   
    //S-type, sw JLP
    if(opcode == "0100011") { //if sw, same as lw, with mem_write true JLP
        alu_op = 00;
        mem_read = true;
        mem_write = true;
        alu_src = true;         //for Mux 0 or 1
        alu_ctrl = Alu_Ctrl(funct_3, funct_7, alu_op);
    }

    //if SB JLP
    if(opcode == "1100011") {
        branch = true;
        alu_op = 01;
    }


    ///*
        //if JALR 1100111 is an I instruction...
        if(opcode == "1100111") {
            alu_op = 00; //set to add
            //branch = true; 
            alu_src = true;
            reg_write = true; //writing the return address back
            
        }
         //JAL 1101111
         if(opcode == "1101111") {
            alu_op == 00; //set to add
            //branch = true;
            reg_write = true; 
            alu_src = true;

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
        int file_position = (pc/4 - 1) * 34; 
        instruction_file.seekg(file_position);
        
        //pull instruction
        getline(instruction_file, instruction_fetched);
        //check this works
        //cout << "Instruction fetched: " << instruction_fetched << "\n";
    }

    //find eof()
    int file_position = (pc/4) * 34; 
    string dummy_line;
    instruction_file.seekg(file_position);
    //pull instruction
    getline(instruction_file, dummy_line);
    if(!instruction_file.eof()){
        if_more_instr = true;
    }else{
        if_more_instr = false;
    }

    instruction_file.close();

    //After fetching instruction
    next_pc = pc + 4;
}

void Cpu::Execute(){
    //cout << "alu_ctrl: " << alu_ctrl << "\n";
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

    alu_zero = false;
    if(branch){
        branch_target = next_pc + (read_imme << 1);
        if(alu_output == 0){
            alu_zero == true;
        }
    }
    //cout << "alu_output: " << alu_output << "\n";
}


void Cpu::Writeback(){
    //Cycle complete increment total clock cycles
    total_clock_cycles++;
    cout << "Total Clock Cycle " << total_clock_cycles << " :\n"; 

    //if writing to memory we don't need to write back
    if(reg_write){
        if(mem_to_reg){
            //read data read in Mem() by LW
            rf[dest_reg] = read_d_mem;
            cout << "x" << dest_reg << " is modified to 0x" << hex << read_d_mem << "\n";

        }
        else{
            //read data from ALU_output and store in register
            rf[dest_reg] = alu_output;
            cout << "x" << dest_reg << " is modified to 0x" << hex <<  alu_output << "\n";
        }
    }
    
    //for printing and nothing else
    if(mem_write){
        cout << "memory 0x" << hex << alu_output << " is modified to 0x" << hex <<  read_data_s << "\n";

    }

    cout << "PC is modified to 0x" << hex << pc << "\n";
}