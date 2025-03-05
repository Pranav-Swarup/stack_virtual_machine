#include "stack-vm.h"
#include <cstdint>
#include <string>
using namespace std;
/* 23BCE5121 23BCE1258 23BCE5119
 *
 * Instruction format
 * header: 2 bits
 * data: 30 bits
 *
 * header format
 *
 * 0 => positive integer
 * 1 => primitive instruction
 * 2 => negative integer
 * 3 => string
 */

//functions

StackVM::StackVM(){
	memory.reserve(100000);
}

i32 StackVM::getType(i32 instruction) {

   	 return (instruction & 0xC0000000) >> 30; // Ensuring it treats top 2 bits correctly
	// every instruction has a 2 bit header which specifies the type 
	// of the insturction. See header format
	// >> 30 right shifts so that the signed interpretation isnt taken. 
}

i32 StackVM::getData(i32 instruction){
	i32 data = 0x3fffffff;
	data = (data & instruction);
	return data;
}

void StackVM::fetch(){
	pc++;
}

void StackVM::decode(){
	
    typ = getType(static_cast<uint32_t>(memory[pc]));
    dat = getData(static_cast<uint32_t>(memory[pc]));
    //cout << "Type is: " << typ << endl;
    switch(typ){
		case 0:
			cout << "Fetched data: " << hex << dat << " --> POS INTEGER " << endl;
       			break;
		case 1:
			cout << "Fetched data: " << hex << dat << " --> INSTRUCTION " << endl;
			break;
		case 2:
			cout << "Fetched data: " << hex << dat << " --> NEG INTEGER " << endl;
			break;
		case 3:
			cout << "Fetched data: " << static_cast<char>(dat) << " --> STRING " << endl;
			break;
		default:
			cout << "Fetched data: " << hex << dat << " --> UNDEFINED" << endl;
	}
}

void StackVM::execute(){
	if(typ==0 || typ ==2 || typ==3){
		sp++;
		memory[sp] = dat;

	// most stacks grow downwards. this one starts at 0 and grows up.
	} else{
		cout << "Decoded instruction: " << dat << endl;
		doPrimitive();
	}
}

void StackVM::doPrimitive(){
	i32 start, end;
	string str;
switch(dat){
    case 0: // halt
        cout << "Virtual Machine halted" << endl;
        running = 0;
        break;
    case 1: // add
        cout << "Adding: " << memory[sp-1] << " and " << memory[sp] << endl;
        memory[sp-1] = memory[sp-1] + memory[sp];
        sp--;
        break;
    case 2: // subtract
        cout << "Subtract: " << memory[sp-1] << " and " << memory[sp] << endl;
        memory[sp-1] = memory[sp-1] - memory[sp];
        sp--;
        break;
    case 3: // mul
        cout << "Multiply: " << memory[sp - 1] << " and " << memory[sp] << endl;
        memory[sp - 1] = memory[sp - 1] * memory[sp];
        sp--;
        break;
    case 4: // div
        cout << "Divide " << memory[sp - 1] << " and " << memory[sp] << endl;
        memory[sp - 1] = memory[sp - 1] / memory[sp];
        sp--;
        break;
    case 9: // push_str
	    str = "";
   	 cout << "Storing string to buffer..." << endl;
	    cout << "Stack contents before reading: ";
    for (i32 i = sp; i >= 0; i--) {  // Print the relevant part of the stack
        cout << hex << memory[i] << " ";
    }
    cout << endl;    
    end = sp;  // End of string (top of stack)
    
    // Find the start of the string (null terminator location)
    while (memory[sp] != 0) {
        sp--; 
    }
    
    start = sp + 1; // First character of the string (after null terminator)
    
    // Extract the string in correct order
    for (i32 i = start; i <= end; i++) {
        str += static_cast<char>(memory[i]);
    }

    stringBuffer[start] = str;  // Store in buffer at the correct index
    cout << "Stored: \"" << str << "\" at index " << start << endl;
    break;

    case 10: // get_str
        cout << "Getting string" << endl;
        break;
	}
}
void StackVM::run(){
    pc -= 1;
    while (running == 1){
        fetch();
        decode();
        execute();
        cout << "Top of the Stack --> " << memory[sp] << endl;
    }
}

void StackVM::loadProgram(vector<i32> prog){
    for(i32 i = 0; i < prog.size(); i++){
        memory[pc + i] = prog[i];
    }
}

