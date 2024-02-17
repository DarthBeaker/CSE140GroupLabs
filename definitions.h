//define the field sizes to avoid magic numbers JLP
const int instrSz = 32;    
const int opCodeSz = 7; 
const int funct3Sz = 3;
const int funct7Sz = 7;
const int rdSz = 5; 
const int rsSz = 5; 
const int ImmI = 5; 
const int ImmSz2 = 16; 

//function definitions
void print_instructions(char*); //main function will call subfunctions KP
char parse_instructions(char*); //find the opcode, returns instruct type KP
int parse_funct3(char*);
int parse_funct7(char*);
int parse_immediate(char*);
int parse_register(char*);