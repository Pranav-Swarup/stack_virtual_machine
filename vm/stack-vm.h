#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <vector>
#include <unordered_map>

typedef int32_t i32;

class StackVM{
	i32 pc = 100;  //program counter starts at address 100
	i32 sp = 0;
	std::vector<i32> memory;
	i32 typ = 0;
	i32 dat = 0;
	i32 running = 1;

	std::unordered_map<i32, std::string> stringBuffer;
	i32 strAddress = 1000; // Arbitrary start address for strings
	
	// get type function
	i32 getType(i32 instruction);
	i32 getData(i32 instruction);
	void fetch();
	void decode();
	void execute();
	void doPrimitive(); //helper function for execute

	public: 
	StackVM(); // contructor
	void run();
	void loadProgram(std::vector<i32> prog);

};

#endif
