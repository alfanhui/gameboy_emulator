#include <iostream>
#include <string>
#include "CPU.h"
#include "MMU.h"
#include <uchar.h>


CPU::CPU() {
	reg = new CPURegister();
	reg->write16(reg, PC, 0x100);
}

void CPU::runInstruction(uint8_t opcode, uint8_t n)
{
	switch (opcode) {
		case 0x06: case 0x0E: case 0x16: case 0x1E:	case 0x26: case 0x2E:
			LDnn_n(opcode, n); 
			break;
		
		default: 
			std::cout << "Instruction not mapped." << std::endl;
	}
}

//all variations 8 cycles
void CPU::LDnn_n(uint8_t opcode, uint8_t n) {
	reg->write8(reg, ((opcode + 2) / 8) - 1, n);
}

void CPU::destroyCpu(CPU* cpu) {
	delete cpu;
}
