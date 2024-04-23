#include "cpu.cpp"
#include <iostream>

using namespace std;



int main(){
    //first initalize test variables
    string test_file_name;
    Cpu test_cpu;


    cout << "Enter the program file name to run: ";
    getline(cin, test_file_name);
    //First run fetch
    while(test_cpu.IfMoreInstr()){
        test_cpu.Fetch(test_file_name);
        test_cpu.Decode();
        test_cpu.Execute();
        test_cpu.Mem();
        test_cpu.Writeback();
        // cout << "Total Clock Cycle " << test_cpu.getTotalCycles() << " :\n"; 
        // cout << "PC is modified to " << test_cpu.getPC() << "\n";
    }
    return 0;
}