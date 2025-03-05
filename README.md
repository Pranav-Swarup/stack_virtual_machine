# Stack-Based Virtual Machine
This project implements a stack-based virtual machine (VM) that processes custom assembly-like instructions. 
It includes an assembler (sasm.cpp) to convert .sasm files into machine code (out.bin) and a VM (stack-vm.cpp) to execute these instructions.

## Features

- Stack-based execution model
- Supports arithmetic (+, -, *, /)
- String storage & retrieval (push_str, get_str)
- Custom instruction encoding

## How to Use it

### Download all the directories and files in them.

### Create an executable of your Stack VM:

- Go to vm directory
- Remove any existing out.bin (if any)
- $ make clean
- $ make
You should have an executable 'stack-vm'

### Assemble the program:

Go to sasm directory and open sasm.cpp for a list of instructions which are allowed for the machine.
Modify test.sasm with your instructions. For example - ("hello" push_str get_str 3 4 + 2 *) will 
1. Store the string hello to the buffer
2. Retrieve it and print it
3. Add 3 and 4
4. Multiply (3+4) with 2

- $ make clean
- $ make
- $ ./sasm test.sasm

You now have a out.bin file storing your instructions in binary form. 

### Run the VM:

Move the out.bin to your vm directory or simple ensure that the 'stack-vm' executable can access it (if they are in the same directory)
Run $ ./stack-vm out.bin

This will execute test.sasm on the stack-based VM. 

## Project Structure
1. stack-vm.cpp	- Core VM implementation that executes instructions by manipulating a stack.
2. stack-vm.h	- Header file defining the VM class, stack operations, and memory management, both for stack and string Buffer.
3. sasm.cpp - 	Assembler that translates .sasm files into machine-readable binary (out.bin).
4. test.sasm -	User input via assembly program to test the VM, including arithmetic and string operations.
5. out.bin -	Binary output of sasm.cpp, fed into stack-vm for execution.
6. Makefile	- Automates compilation of the assembler and VM.

Pranav Swarup 2025 ©
________________________
References: https://github.com/pbohun/stack-vm-tutorials 
