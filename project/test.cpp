#include "cpu.cpp"
#include <iostream>

using namespace std;



int main(){
    //first initalize test variables
    string test_file_name;
    Cpu test_cpu;


    cout << "Enter the program file name to run: ";
    getline(cin, test_file_name);
    cout << "\n"; //spacing in example output
    //First run fetch
    while(test_cpu.IfMoreInstr()){
        test_cpu.Fetch(test_file_name);
        test_cpu.Decode();
        test_cpu.Execute();
        test_cpu.Mem();
        test_cpu.Writeback();
        cout << "\n"; //spacing in example output
    }
    cout << "program terminated: \n";
    cout << "total execution time is " << test_cpu.getTotalCycles() << " cycles \n";
    return 0;
}